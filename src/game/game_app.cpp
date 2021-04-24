#include "game_app.h"

#include <glad/glad.h>

bool GameApp::onInit() {
  _blockAtlas.init();
  _tetromino.init();

  _camera.setAspectRatio(1.6f/0.9f);

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {
  LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);
}

void GameApp::onUpdate(const UpdateContext& ctx) {
  static float time = 0.0f;

  time += ctx.frameTime;

  const float zoom = sinf(time) + 1.25f;
  _camera.setZoom(zoom);

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _tetromino.render(_blockAtlas, _camera.getViewProjectionMatrix());
}
