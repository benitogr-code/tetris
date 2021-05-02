#include "game_app.h"

#include <glad/glad.h>

static constexpr float kBlockSize = 32.0f;
static constexpr float kPadding = 10.0f;
static constexpr int   kFontSize = 20;

static constexpr int kBoardColumns = 10;
static constexpr int kBoardRows = 20;
static constexpr float kBoardWidth = kBoardColumns * kBlockSize;
static constexpr float kBoardHeight = kBoardRows * kBlockSize;
static constexpr float kUIWidth = 160.0f;

static constexpr float kViewportWidth = (kBoardWidth + kUIWidth) + (kPadding*4.0f);
static constexpr float kViewportHeight = kBoardHeight + (kPadding*2.0f);

static constexpr glm::vec3 kColorBlack = {0.0f, 0.0f, 0.0f};
static constexpr glm::vec3 kColorWhite = {1.0f, 1.0f, 1.0f};

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

// GameApp
GameApp::GameApp()
  : _blockRenderer(kBlockSize)
  , _board(kBoardColumns, kBoardRows, kBlockSize)
  , _tetromino(kBlockSize)
  , _nextTetromino(kBlockSize) {

}

bool GameApp::onInit() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _blockRenderer.init();
  _textRenderer.init(kFontSize);

  _board.setOrigin({ kViewportWidth - kBoardWidth - kPadding, kPadding });
  respawnTetromino();

  _camera = CameraOrthographic(0.0f, kViewportWidth, 0.0f, kViewportHeight);

  getWindow()->resize(kViewportWidth, kViewportHeight);

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {

  if ((event.keyId == KeyId_Enter) && (event.state == InputState_Pressed)) {
    respawnTetromino();
  }
  else if ((event.keyId == KeyId_Space) && (event.state == InputState_Pressed) != 0) {
    const std::array<glm::ivec2, 10> offsets = {
      glm::ivec2(0 , 0), glm::ivec2(1 , 0), glm::ivec2(2 , 0), glm::ivec2(-1 , 0), glm::ivec2(-2 , 0),
      glm::ivec2(0 , 1), glm::ivec2(1 , 1), glm::ivec2(2 , 1), glm::ivec2(-1 , 1), glm::ivec2(-2 , 1)
    };

    for (int i = 0; i < offsets.size(); ++i) {
      const auto location = _tetrominoBoardLocation + offsets[i];

      if (canRotate(_tetromino, _board, location)) {
        moveAndRotateTetromino(location);
        break;
      }
    }
  }
  else if ((event.keyId == KeyId_Left) && (event.state == InputState_Pressed)) {
    const auto location = _tetrominoBoardLocation + glm::ivec2(-1, 0);

    if (canMoveTo(_tetromino, _board, location)) {
      moveTetromino(location);
    }
  }
  else if ((event.keyId == KeyId_Right) && (event.state == InputState_Pressed)) {
    const auto location = _tetrominoBoardLocation + glm::ivec2(1, 0);

    if (canMoveTo(_tetromino, _board, location)) {
      moveTetromino(location);
    }
  }
  else if ((event.keyId == KeyId_Down) && (event.state == InputState_Pressed)) {
    const auto location = _tetrominoBoardLocation + glm::ivec2(0, -1);

    if (canMoveTo(_tetromino, _board, location)) {
      moveTetromino(location);
    }
  }
}

void GameApp::onUpdate(const UpdateContext& ctx) {
  glClearColor(kColorBlack.r, kColorBlack.g, kColorBlack.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  const auto& vpMatrix = _camera.getViewProjectionMatrix();

  _blockRenderer.beginFrame(vpMatrix);
  {
    _board.render(_blockRenderer);
    _tetromino.render(_blockRenderer);
    _nextTetromino.render(_blockRenderer);
  }
  _blockRenderer.endFrame();

  // Game state message
  {
    const glm::vec2 textPos = _board.getOrigin() + glm::vec2(kBoardWidth / 4.0f, kBoardHeight * 0.6f);
    _textRenderer.drawText("Game Over", textPos, kColorWhite, 1.0f, vpMatrix);
  }

  // Next tetromino
  {
    const glm::vec2 textPos = { kPadding, kViewportHeight - kFontSize - kPadding };
    _textRenderer.drawText("Next", textPos, kColorWhite, 1.0f, vpMatrix);

    const glm::vec2 tetrominoPos = textPos - glm::vec2(0.0f, (kBlockSize * 4.0f) + kPadding);
    _nextTetromino.setPosition(tetrominoPos);
  }

  // Score
  {
    const glm::vec2 startPos = { kPadding, kViewportHeight / 2 };
    const std::array<std::string, 4> messages = { "Score", "250", "Lines", "3" };

    for (int i = 0; i < messages.max_size(); ++i) {
      const glm::vec2 textPos = startPos - glm::vec2(0.0f, (kFontSize + kPadding) * i);
      _textRenderer.drawText(messages[i], textPos, kColorWhite, 1.0f, vpMatrix);
    }
  }
}

void GameApp::moveTetromino(const glm::ivec2& boardLocation) {
  _tetrominoBoardLocation = boardLocation;
  auto& boardOrigin = _board.getOrigin();
  auto  boardPosition = glm::vec2(boardLocation.x * kBlockSize, boardLocation.y * kBlockSize);
  _tetromino.setPosition(boardOrigin + boardPosition);
}

void GameApp::moveAndRotateTetromino(const glm::ivec2& boardLocation) {
  moveTetromino(boardLocation);
  _tetromino.rotate();
}

void GameApp::respawnTetromino() {
  glm::ivec2 location = {(kBoardColumns/2 - 2), (kBoardRows-4)};
  moveTetromino(location);
  _tetromino.randomize();
}
