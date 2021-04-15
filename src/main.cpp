#include "system/application.h"

class DemoApp: public Application {
protected:
  bool onInit() {
    return true;
  }

  void onShutdown() {
  }

  void onUpdate() {
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
