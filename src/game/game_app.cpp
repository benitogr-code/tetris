#include "game_app.h"

static constexpr float kBlockSize = 28.0f;
static constexpr float kPadding = 10.0f;
static constexpr int   kFontSize = 20;

static constexpr int kBoardColumns = 12;
static constexpr int kBoardRows = 20;
static constexpr float kBoardWidth = kBoardColumns * kBlockSize;
static constexpr float kBoardHeight = kBoardRows * kBlockSize;
static constexpr float kUIWidth = 160.0f;

static constexpr float kViewportWidth = (kBoardWidth + kUIWidth) + (kPadding*4.0f);
static constexpr float kViewportHeight = kBoardHeight + (kPadding*2.0f);

static constexpr glm::vec3 kColorBlack = {0.0f, 0.0f, 0.0f};
static constexpr glm::vec3 kColorWhite = {1.0f, 1.0f, 1.0f};

static constexpr float kTetrominoMoveTime = 0.45f;
static constexpr float kTetrominoNormalSpeed = 1.0f;
static constexpr float kTetrominoDropSpeed = 7.0f;

static constexpr float kClearRowsTime = 0.7f;
static constexpr std::array<uint32_t, 4> kScores = {50, 125, 250, 400};

// Helpers
bool canMoveTo(const Tetromino& tetromino, const Board& board, const glm::ivec2& location) {
  std::vector<glm::ivec2> coords;
  tetromino.getBlockCoordinates(location, coords);

  bool canMove = true;
  for (const auto& value : coords) {
    canMove &= board.isBlockEmpty(value.x, value.y);
  }

  return canMove;
}

bool canRotate(const Tetromino& tetromino, const Board& board, const glm::ivec2& location) {
  std::vector<glm::ivec2> coords;
  tetromino.getBlockCoordinatesAfterRotation(location, coords);

  bool canRotate = true;
  for (const auto& value : coords) {
    canRotate &= board.isBlockEmpty(value.x, value.y);
  }

  return canRotate;
}

void addToBoard(const Tetromino& tetromino, Board& board, const glm::ivec2& location) {
  std::vector<glm::ivec2> coords;
  tetromino.getBlockCoordinates(location, coords);

  for (const auto& value : coords) {
    board.setBlock(value.x, value.y, tetromino.getBlockId());
  }
}

// GameApp
GameApp::GameApp()
  : _renderer(kBlockSize, kFontSize)
  , _board(kBoardColumns, kBoardRows, kBlockSize)
  , _boardTetromino(kBlockSize)
  , _uiTetromino(kBlockSize) {

}

bool GameApp::onInit() {
  _camera = CameraOrthographic(0.0f, kViewportWidth, 0.0f, kViewportHeight);

  _renderer.init();
  _renderer.setClearColor(kColorBlack);

  _board.setOrigin({ kViewportWidth - kBoardWidth - kPadding, kPadding });

  getWindow()->resize(kViewportWidth, kViewportHeight);

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {
  switch (_gameState) {
    case GameState::PreGame: {
      const bool startGame = (event.keyId == KeyId_Enter) && (event.state == InputState_Pressed);

      if (startGame) {
        changeGameState(GameState::Running);
      }
    }
    break;
    case GameState::Running: {
      if ((event.keyId == KeyId_Escape) && (event.state == InputState_Pressed)) {
        changeGameState(GameState::Paused);
      }
      else if ((event.keyId == KeyId_Space) && (event.state == InputState_Pressed) != 0) {
        const std::array<glm::ivec2, 10> offsets = {
          glm::ivec2(0 , 0), glm::ivec2(1 , 0), glm::ivec2(2 , 0), glm::ivec2(-1 , 0), glm::ivec2(-2 , 0),
          glm::ivec2(0 , 1), glm::ivec2(1 , 1), glm::ivec2(2 , 1), glm::ivec2(-1 , 1), glm::ivec2(-2 , 1)
        };

        for (int i = 0; i < offsets.size(); ++i) {
          const auto location = _boardTetrominoLocation + offsets[i];

          if (canRotate(_boardTetromino, _board, location)) {
            moveAndRotateTetromino(location);
            break;
          }
        }
      }
      else if ((event.keyId == KeyId_Left) && (event.state == InputState_Pressed)) {
        const auto location = _boardTetrominoLocation + glm::ivec2(-1, 0);

        if (canMoveTo(_boardTetromino, _board, location)) {
          moveTetromino(location);
        }
      }
      else if ((event.keyId == KeyId_Right) && (event.state == InputState_Pressed)) {
        const auto location = _boardTetrominoLocation + glm::ivec2(1, 0);

        if (canMoveTo(_boardTetromino, _board, location)) {
          moveTetromino(location);
        }
      }
      else if (event.keyId == KeyId_Down) {
        if((event.state == InputState_Pressed) || (event.state == InputState_Hold)) {
          _boardTetrominoSpeed = kTetrominoDropSpeed;
        }
        else {
          _boardTetrominoSpeed = kTetrominoNormalSpeed;
        }
      }
    }
    break;
    case GameState::Paused: {
      if ((event.keyId == KeyId_Escape) && (event.state == InputState_Pressed)) {
        changeGameState(GameState::Running);
      }
    }
    break;
    case GameState::GameOver: {
      const bool endGame = (event.keyId == KeyId_Enter) && (event.state == InputState_Pressed);

      if (endGame) {
        changeGameState(GameState::PreGame);
      }
    }
    break;
  };
}

void GameApp::onUpdate(const UpdateContext& ctx) {
  _gameTime += ctx.frameTime;

  _renderer.beginFrame(_camera.getViewProjectionMatrix());

  switch (_gameState) {
    case GameState::PreGame: {
      const float textScale = 1.5f + ((sinf(_gameTime) + 1.0f)*0.3f);
      const glm::vec2 textPos = { kViewportWidth * 0.5f, (kViewportHeight * 0.5f) - (kFontSize * textScale * 0.5f)};
      _renderer.drawTextCentered("Press ENTER to play", textPos, kColorWhite, textScale);
    };
    break;
    case GameState::Running: {
      if (_clearingRows) {
        _clearRowsTimeout -= ctx.frameTime;

        if (_clearRowsTimeout <= 0.0f) {
          auto count = _board.clearFullRows();
          _stats.lines += count;
          _stats.score += kScores[count-1];
          _clearRowsTimeout = -1.0f;
          _clearingRows = false;
        }
      }
      else {
        const float nextMove = _boardTetrominoNextMove - (ctx.frameTime * _boardTetrominoSpeed);
        if (nextMove <= 0.0f) {
          const auto location = _boardTetrominoLocation + glm::ivec2(0, -1);

          if (canMoveTo(_boardTetromino, _board, location)) {
            moveTetromino(location);
          }
          else {
            addToBoard(_boardTetromino, _board, _boardTetrominoLocation);
            respawnTetromino();

            if (!canMoveTo(_boardTetromino, _board, _boardTetrominoLocation)) {
              changeGameState(GameState::GameOver);
            }
            else if (_board.hasFullRows()){
              _clearingRows = true;
              _clearRowsTimeout = kClearRowsTime;
            }
          }

          _boardTetrominoNextMove = kTetrominoMoveTime + nextMove;
        }
        else {
          _boardTetrominoNextMove = nextMove;
        }
      }

      if (_clearingRows)
        drawBoardClearing(1.0f - (_clearRowsTimeout / kClearRowsTime));
      else
        drawBoard();

      drawGameUI();
    }
    break;
    case GameState::Paused: {
      drawBoardWithMessage("PAUSED");
      drawGameUI();
    }
    break;
    case GameState::GameOver: {
      drawBoardWithMessage("GAME OVER");
      drawGameUI();
    }
    break;
  }

  _renderer.endFrame();
}

void GameApp::drawGameUI() {
  {
    const glm::vec2 topLeft = { kPadding * 1.5f, kViewportHeight - kFontSize - kPadding };
    _renderer.drawText("Next", topLeft, kColorWhite, 1.2f);

    const glm::vec2 tetrominoPos = topLeft - glm::vec2(0.0f, (kBlockSize * 4.0f) + kPadding);
    _uiTetromino.setPosition(tetrominoPos);
    _uiTetromino.render(_renderer);
  }

  // Score
  {
    const glm::vec2 midLeft = { kPadding * 1.5f, kViewportHeight / 2 };
    const std::array<std::string, 4> messages = { "Score", std::to_string(_stats.score), "Lines", std::to_string(_stats.lines) };

    for (int i = 0; i < messages.max_size(); ++i) {
      const glm::vec2 textPos = midLeft - glm::vec2(0.0f, (kFontSize + kPadding) * i);
      _renderer.drawText(messages[i], textPos, kColorWhite, 1.2f);
    }
  }
}

void GameApp::drawBoard() {
  _board.render(_renderer);
  _boardTetromino.render(_renderer);
}

void GameApp::drawBoardClearing(float clearingPercentage) {
  _board.render(_renderer, clearingPercentage);
}

void GameApp::drawBoardWithMessage(const std::string& message) {
  drawBoard();

  const glm::vec2 messagePos = _board.getOrigin() + glm::vec2(kBoardWidth / 2.0f, kBoardHeight * 0.5f);
  _renderer.drawTextCentered(message, messagePos, kColorWhite, 1.4f);
}

void GameApp::changeGameState(GameState state) {
  if (_gameState == state)
    return;

  if (state == GameState::PreGame) {
    _board.reset();
    _stats.score = 0;
    _stats.lines = 0;
  }
  else if (state == GameState::Running) {
    if (_gameState == GameState::PreGame) {
      respawnTetromino();
    }

    _boardTetrominoSpeed = kTetrominoNormalSpeed;
  }

  _gameState = state;
}

void GameApp::moveTetromino(const glm::ivec2& boardLocation) {
  _boardTetrominoLocation = boardLocation;
  auto& boardOrigin = _board.getOrigin();
  auto  boardPosition = glm::vec2(boardLocation.x * kBlockSize, boardLocation.y * kBlockSize);
  _boardTetromino.setPosition(boardOrigin + boardPosition);
}

void GameApp::moveAndRotateTetromino(const glm::ivec2& boardLocation) {
  moveTetromino(boardLocation);
  _boardTetromino.rotate();
}

void GameApp::respawnTetromino() {
  _boardTetromino.clone(_uiTetromino);
  _boardTetrominoNextMove = kTetrominoMoveTime;
  _uiTetromino.randomize();

  glm::ivec2 location = {(kBoardColumns/2 - 2), (kBoardRows-3)};
  moveTetromino(location);
}
