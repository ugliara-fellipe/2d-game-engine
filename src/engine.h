#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct engine_s {
  SDL_Window *window;
  SDL_Renderer *render;
  bool running;
} engine_t;

#endif
