#include "system/application.h"

class DemoApp: public Application {
protected:
  virtual bool onInit() override {
    return true;
  }

  virtual void onShutdown() override {
  }

  virtual void onInputEvent(const InputEvent& event) override {
    LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);
  }

  virtual void onUpdate() override {
  }
};

Application* createApplication() {
  return new DemoApp();
}

int main(int argsCount, char** args) {
  StartupParams params;
  params.appCreatorFunc = createApplication;
  params.windowDesc.width = 800;
  params.windowDesc.height = 600;
  params.windowDesc.title = "Tetris";

  return startApplication(params);
}
