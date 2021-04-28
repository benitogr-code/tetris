#include "game_app.h"
#include "system/render_device.h"

bool GameApp::onInit() {
  _blocksMaterial = std::make_shared<BlocksMaterial>();
  _blocksMaterial->init();
  _tetromino.init(_blocksMaterial);

  _camera.setAspectRatio(1.6f/0.9f);

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {
  LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);
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

  _tetromino.render(renderDevice);
}
