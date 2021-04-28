#include "game_app.h"
#include "system/render_device.h"

bool GameApp::onInit() {
  _blocksMaterial = std::make_shared<BlocksMaterial>();
  _blocksMaterial->init();

  _tetrominoA.init(0.1f, _blocksMaterial);
  _tetrominoA.setPosition({-0.7f, 0.0f});
  _tetrominoB.init(0.1f, _blocksMaterial);
  _tetrominoB.setPosition({0.7f, 0.0f});

  _camera.setAspectRatio(1.6f/0.9f);

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {
  LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);

  if ((event.keyId == KeyId_Up) && (event.state == InputState_Pressed)) {
    _tetrominoA.rotate();
    _tetrominoB.rotate();
  }
  else if ((event.keyId == KeyId_Escape) && (event.state == InputState_Pressed)) {
    _tetrominoA.randomize();
    _tetrominoB.randomize();
  }
}

void GameApp::onUpdate(const UpdateContext& ctx) {
  /*
  static float time = 0.0f;

  time += ctx.frameTime;

  const float zoom = sinf(time) + 1.25f;
  _camera.setZoom(zoom);
  */

  auto& renderDevice = getRenderDevice();

  renderDevice.clear(0.5f, 0.5f, 0.5f);
  renderDevice.beginRendering(_camera.getViewProjectionMatrix());

  _tetrominoA.render(renderDevice);
  _tetrominoB.render(renderDevice);
}
