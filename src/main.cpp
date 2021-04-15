#include <glad/glad.h>
#include <SDL.h>

#include "system/Logger.h"

int main(int argsCount, char** args) {
  Logger::init();

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_ERROR("Fail to initialize SDL");

    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  const uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
  SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, flags);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

  LOG_INFO("SDL window created");

  bool running = true;
  while (running) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
      if (Event.type == SDL_QUIT) {
        running = false;
      }
    }

    SDL_GL_SwapWindow(window);
  }

  LOG_INFO("Closing application");

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
