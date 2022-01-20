/*
MIT License

Copyright (c) 2022 Fellipe Augusto Ugliara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "game.h"

const char *game_name() { return "Game"; }

static SDL_Texture *texture = NULL;
static int exit_count = 1000;

void game_init() {
  trace_debug("game_init\n");

  SDL_Surface *bmp = SDL_LoadBMP("assets/grumpy-cat.bmp");
  if (bmp == NULL) {
    trace_error("SDL_LoadBMP Error: %s\n", SDL_GetError());
    engine->running = false;
    return;
  }

  texture = SDL_CreateTextureFromSurface(engine->render, bmp);
  if (texture == NULL) {
    trace_error("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    SDL_FreeSurface(bmp);
    engine->running = false;
    return;
  }
  SDL_FreeSurface(bmp);
}

void game_process_events(SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYDOWN:
    trace_debug("game_process_events:  Key press detected\n");
    break;

  case SDL_KEYUP:
    trace_debug("game_process_events:  Key release detected\n");
    engine->running = false;
    break;

  default:
    break;
  }
}

void game_fixed_update(real_t delta) {
  trace_debug("game_fixed_update:    delta: %f\n", delta);
  if (exit_count == 0) {
    engine->running = false;
  } else {
    exit_count--;
  }
}

void game_variable_update(real_t delta) {
  trace_debug("game_variable_update: delta: %f\n", delta);
}

void game_render(real_t delta) {
  trace_debug("game_render:          delta: %f\n", delta);
  SDL_RenderCopy(engine->render, texture, NULL, NULL);
}

void game_exit() {
  trace_debug("game_exit\n");

  if (texture == NULL) {
    SDL_DestroyTexture(texture);
  }
}
