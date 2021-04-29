#include "game_app.h"

#include <glad/glad.h>

#define BLOCK_SIZE 1.0f

#define BOARD_WIDHT  12
#define BOARD_HEIGHT 20

GameApp::GameApp()
  : _blockRenderer(BLOCK_SIZE)
  , _board(BOARD_WIDHT, BOARD_HEIGHT) {
}

bool GameApp::onInit() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _blockRenderer.init();

  _tetrominos[0].setPosition({  4.0f * BLOCK_SIZE, 4.0f * BLOCK_SIZE });
  _tetrominos[1].setPosition({  4.0f * BLOCK_SIZE, 10.0f * BLOCK_SIZE });

  _camera.setAspectRatio(800.0f/600.0f);
  _camera.setZoom(11.0f);
  _camera.setPosition({ 0.0f, 10.0f });

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {
  //LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);

  if ((event.keyId == KeyId_Up) && (event.state&InputState_Pressed) != 0) {
    for (auto& t : _tetrominos) {
      t.rotate();
    }
  }
  else if ((event.keyId == KeyId_Escape) && (event.state == InputState_Pressed)) {
    for (auto& t : _tetrominos) {
      t.randomize();
    }
  }
}

void GameApp::onUpdate(const UpdateContext& ctx) {
  /*
  static float time = 0.0f;

  time += ctx.frameTime;

  const float zoom = sinf(time) + 1.25f;
  _camera.setZoom(zoom);
  */

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  _blockRenderer.beginFrame(_camera.getViewProjectionMatrix());
  {
    _board.render(_blockRenderer);

    for (auto& t : _tetrominos) {
      t.render(_blockRenderer);
    }
  }
  _blockRenderer.endFrame();
}
