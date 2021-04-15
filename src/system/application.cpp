#include "application.h"
#include "logger.h"

#include <glad/glad.h>
#include <SDL.h>

Application::Application()
  : _running(true) {
}

Application::~Application() {
}

bool Application::init() {
  bool success = onInit();

  return success;
}

void Application::shutdown() {
  onShutdown();
}

void Application::run() {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  const uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
  SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, flags);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

  LOG_INFO("SDL window created");

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

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
}
