#include "game/game_app.h"

Application* createApplication() {
  return new GameApp();
}

int main(int argsCount, char** args) {
  StartupParams params;
  params.appCreatorFunc = createApplication;
  params.windowDesc.width = 1280;
  params.windowDesc.height = 720;
  params.windowDesc.title = "Tetris";

  return startApplication(params);
}
