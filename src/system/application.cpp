#include "application.h"
#include "input.h"

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

  _input.reset(new Input());
  _input->registerCallback(std::bind(&Application::onInputEvent, this, std::placeholders::_1));

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
    // Handle input + events
    SDL_PumpEvents();

    checkSystemEvents();
    _input->update();

    // Run logic
    onUpdate();

    // Render
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _window->update();
  }
}

void Application::checkSystemEvents() {
  const int maxEvents = 16;
  SDL_Event events[maxEvents];
  const int eventsRead = SDL_PeepEvents(events, maxEvents, SDL_GETEVENT, SDL_QUIT, SDL_QUIT);

  for (int i = 0; i < eventsRead; ++i) {
    if (events[i].type == SDL_QUIT) {
      _running = false;
      break;
    }
  }
}
