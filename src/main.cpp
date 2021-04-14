#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

int main(int argsCount, char** args) {
  const uint32_t flags = SDL_WINDOW_OPENGL;
  SDL_Window *window = SDL_CreateWindow("Tetris", 0, 0, 800, 600, flags);
  SDL_GL_CreateContext(window);

  bool running = true;
  while (running) {
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
      if (Event.type == SDL_KEYDOWN) {
        running = Event.key.keysym.sym != SDLK_ESCAPE;
      }
      else if (Event.type == SDL_QUIT) {
        running = false;
      }
    }

    SDL_GL_SwapWindow(window);
  }
  return 0;
}
