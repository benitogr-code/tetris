#include "game_app.h"

#include <glad/glad.h>

#define BLOCK_SIZE 0.15f

GameApp::GameApp()
  : _blockRenderer(BLOCK_SIZE) {
}

bool GameApp::onInit() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _blockRenderer.init();

  _tetrominos[0].setPosition({ -1.0, 0.5f });
  _tetrominos[1].setPosition({  0.0, 0.5f });
  _tetrominos[2].setPosition({  1.0, 0.5f });
  _tetrominos[3].setPosition({ -1.0, -0.5f });
  _tetrominos[4].setPosition({  0.0, -0.5f });
  _tetrominos[5].setPosition({  1.0, -0.5f });

  _camera.setAspectRatio(1.6f/0.9f);
  _camera.setPosition({ 0.25f, 0.0f });

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {
  LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);

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

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  _blockRenderer.beginFrame(_camera.getViewProjectionMatrix());
    for (auto& t : _tetrominos) {
      t.render(_blockRenderer);
    }
  _blockRenderer.endFrame();
}
