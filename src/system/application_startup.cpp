#include "application.h"
#include "file_utils.h"

#include <SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

int startApplication(const StartupParams& params) {
  Logger::init();

  LOG_INFO("Initializing application...");

  FileUtils::init();

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_ERROR("Fail to initialize SDL");
    return -1;
  }

  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    LOG_ERROR("Fail to initialize FreeType");
    return -1;
  }

  auto application = params.appCreatorFunc();
  if (application->init(params.windowDesc)) {
    application->run();
  }

  LOG_INFO("Closing application...");

  application->shutdown();
  delete application;

  FT_Done_FreeType(ft);

  SDL_Quit();

  return 0;
}
