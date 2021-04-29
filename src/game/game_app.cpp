#include "game_app.h"

#include <glad/glad.h>

#define BLOCK_SIZE 25.0f

#define BOARD_WIDHT  12
#define BOARD_HEIGHT 20

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
  : _blockRenderer(BLOCK_SIZE)
  , _board(BOARD_WIDHT, BOARD_HEIGHT, BLOCK_SIZE)
  , _tetromino(BLOCK_SIZE) {

}

bool GameApp::onInit() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _blockRenderer.init();

  _tetrominoBoardLocation = { 4, 4 };
  _tetromino.setPosition({ _tetrominoBoardLocation.x * BLOCK_SIZE, _tetrominoBoardLocation.y * BLOCK_SIZE });

  _camera = CameraOrthographic(0.0f, 800.0f, 0.0f, 600.0f);
  _camera.setPosition({-400.0f, -40.0f});

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {

  if ((event.keyId == KeyId_Enter) && (event.state == InputState_Pressed)) {
    const glm::ivec2 location = {4, 4};
    _tetrominoBoardLocation = location;
    _tetromino.setPosition({ location.x * BLOCK_SIZE, location.y * BLOCK_SIZE });
    _tetromino.randomize();
  }
  else if ((event.keyId == KeyId_Space) && (event.state == InputState_Pressed) != 0) {
    const std::array<glm::ivec2, 10> offsets = {
      glm::ivec2(0 , 0), glm::ivec2(1 , 0), glm::ivec2(2 , 0), glm::ivec2(-1 , 0), glm::ivec2(-2 , 0),
      glm::ivec2(0 , 1), glm::ivec2(1 , 1), glm::ivec2(2 , 1), glm::ivec2(-1 , 1), glm::ivec2(-2 , 1)
    };

    for (int i = 0; i < offsets.size(); ++i) {
      const auto location = _tetrominoBoardLocation + offsets[i];

      if (canRotate(_tetromino, _board, location)) {
        _tetrominoBoardLocation = location;
        _tetromino.setPosition({ location.x * BLOCK_SIZE, location.y * BLOCK_SIZE });
        _tetromino.rotate();
        break;
      }
    }
  }
  else if ((event.keyId == KeyId_Left) && (event.state == InputState_Pressed)) {
    const auto location = _tetrominoBoardLocation + glm::ivec2(-1, 0);

    if (canMoveTo(_tetromino, _board, location)) {
      _tetrominoBoardLocation = location;
      _tetromino.setPosition({ location.x * BLOCK_SIZE, location.y * BLOCK_SIZE });
    }
  }
  else if ((event.keyId == KeyId_Right) && (event.state == InputState_Pressed)) {
    const auto location = _tetrominoBoardLocation + glm::ivec2(1, 0);

    if (canMoveTo(_tetromino, _board, location)) {
      _tetrominoBoardLocation = location;
      _tetromino.setPosition({ location.x * BLOCK_SIZE, location.y * BLOCK_SIZE });
    }
  }
  else if ((event.keyId == KeyId_Down) && (event.state == InputState_Pressed)) {
    const auto location = _tetrominoBoardLocation + glm::ivec2(0, -1);

    if (canMoveTo(_tetromino, _board, location)) {
      _tetrominoBoardLocation = location;
      _tetromino.setPosition({ location.x * BLOCK_SIZE, location.y * BLOCK_SIZE });
    }
  }
}

void GameApp::onUpdate(const UpdateContext& ctx) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  _blockRenderer.beginFrame(_camera.getViewProjectionMatrix());
  {
    _board.render(_blockRenderer);
    _tetromino.render(_blockRenderer);
  }
  _blockRenderer.endFrame();
}
