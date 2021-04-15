#include "application.h"
#include "logger.h"

#include <SDL.h>

int startApplication(const StartupParams& params) {
  Logger::init();

  LOG_INFO("Initializing application...");

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_ERROR("Fail to initialize SDL");

    return -1;
  }

  auto application = params.appCreatorFunc();
  if (application->init(params.windowDesc)) {
    application->run();
  }

  LOG_INFO("Closing application...");

  application->shutdown();
  delete application;

  SDL_Quit();

  return 0;
}
