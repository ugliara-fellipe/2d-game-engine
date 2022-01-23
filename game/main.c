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

static int exit_count = 1000;
static tile_t *tile = NULL;
static v2d_t pos;
static real_t angle = 0;

void game_init() {
  trace_debug("game_init\n");
  assets_texture(0, "assets/grumpy-cat.bmp");
  tile = tile_init(0, v2d_init(100, 100), v2d_init(30, 30));
  pos = v2d_init(500, 250);
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
    if (angle < 360) {
      angle++;
    } else {
      angle = 0;
    }
  }
}

void game_variable_update(real_t delta) {
  trace_debug("game_variable_update: delta: %f\n", delta);
}

void game_render(real_t delta) {
  trace_debug("game_render:          delta: %f\n", delta);
  SDL_Rect dst_rect = {0, 0, 266, 200};
  SDL_RenderCopy(engine->render, assets->texture[0], NULL, &dst_rect);
  draw_tile(tile, pos, angle, SDL_FLIP_NONE);
}

void game_exit() {
  tile_exit(tile);
  trace_debug("game_exit\n");
}
