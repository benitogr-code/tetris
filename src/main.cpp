#include "game/game_app.h"

const char* parseAssetsFolder(int argc, char* argv[]) {
    const char* folder = "";

    for (int i = 0; i < argc - 1; ++i) {
        if (strcmp(argv[i], "--assets") == 0) {
            folder = argv[i+1];
            break;
        }
    }

    return folder;
}

Application* createApplication() {
  return new GameApp();
}

int main(int argc, char* argv[]) {
  StartupParams params;
  params.appCreatorFunc = createApplication;
  params.windowDesc.width = 800;
  params.windowDesc.height = 600;
  params.windowDesc.title = "Tetris";
  params.assetsFolder = parseAssetsFolder(argc, argv);

  return startApplication(params);
}
