#include "game_app.h"

bool GameApp::onInit() {
  return true;
}

void GameApp::onShutdown() {

}

void GameApp::onInputEvent(const InputEvent& event) {
  LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);
}

void GameApp::onUpdate() {
}
