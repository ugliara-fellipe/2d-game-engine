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

#include "engine/engine.h"
#include "engine/monitor.h"
#include "engine/timing.h"
#include "game.h"
#include "toolbelt/trace.h"
#include <stdlib.h>

engine_t *engine = &(engine_t){.window = NULL,
                               .render = NULL,
                               .running = true,
                               .update_rate = 60,
                               .timing_resync = true,
                               .show_fps = true,
                               .font = NULL};

static void engine_init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    trace_crash("SDL_Init Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  engine->window =
      SDL_CreateWindow(game_name(), 100, 100, 800, 450, SDL_WINDOW_SHOWN);
  if (engine->window == NULL) {
    trace_crash("SDL_CreateWindow Error: %s\n", SDL_GetError());
    engine_exit();
    exit(EXIT_FAILURE);
  }

  engine->render = SDL_CreateRenderer(
      engine->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (engine->render == NULL) {
    trace_crash("SDL_CreateRendetexturerer Error: %s\n", SDL_GetError());
    engine_exit();
    exit(EXIT_FAILURE);
  }

  if (TTF_Init() != 0) {
    trace_crash("TTF_Init Error: %s\n", SDL_GetError());
    engine_exit();
    exit(EXIT_FAILURE);
  }

  engine->font = TTF_OpenFont("assets/bgroveb.ttf", 24);
  if (engine->font == NULL) {
    trace_crash("Font not found, TTF_OpenFont\n");
    engine_exit();
    exit(EXIT_FAILURE);
  }
}

void engine_exit() {
  if (TTF_WasInit()) {
    TTF_Quit();
  }
  if (engine->render != NULL) {
    SDL_DestroyRenderer(engine->render);
  }
  if (engine->window != NULL) {
    SDL_DestroyWindow(engine->window);
  }
  SDL_Quit();
}

static void engine_process_events(SDL_Event *event) {
  while (SDL_PollEvent(event)) {
    game_process_events(event);
  }
}

int main(int argc, char *argv[]) {
  // Init
  engine_init();
  monitor_fps_init();
  game_init();
  timing_init();

  SDL_Event event;

  while (engine->running) {
    // Events
    timing_perform();
    engine_process_events(&event);

    // Update
    while (frame_accumulator >= desired_frametime) {
      monitor_fps_increase();
      game_fixed_update(fixed_deltatime);
      if (consumed_delta_time > desired_frametime) {
        game_variable_update(fixed_deltatime);
        timing_consumed_decrease();
      }
      timing_frame_accumulator_decrease();
    }
    real_t delta_update =
        (real_t)consumed_delta_time / SDL_GetPerformanceFrequency();
    game_variable_update(delta_update);

    // Render
    SDL_RenderClear(engine->render);
    real_t delta_render = (real_t)frame_accumulator / desired_frametime;
    game_render(delta_render);
    monitor_fps_render();
    SDL_RenderPresent(engine->render);
  }

  // Exit
  game_exit();
  monitor_fps_exit();
  engine_exit();
  return EXIT_SUCCESS;
}
