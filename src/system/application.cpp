#include "application.h"

#include <glad/glad.h>
#include <SDL.h>

Application::Application()
  : _running(true) {
}

Application::~Application() {
}

bool Application::init(const WindowDesc& desc) {
  _window.reset(new Window(desc));
  if (!_window->init()) {
    LOG_ERROR("Failed to initialize window");

    return false;
  }

  if (!onInit()) {
    LOG_ERROR("Failed to initialize application");

    return false;
  }

  return true;
}

void Application::shutdown() {
  onShutdown();
}

void Application::run() {
  while (_running) {
    onUpdate();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
      if (Event.type == SDL_QUIT) {
        _running = false;
      }
    }

    _window->refresh();
  }
}
