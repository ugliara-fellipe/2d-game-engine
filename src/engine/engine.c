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
#include "assets/assets.h"
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
                               .show_fps = true};

static bool Mix_WasInit = false;

static void engine_init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    trace_crash("SDL_Init Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  engine->window =
      SDL_CreateWindow(game_name(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 800, 450, SDL_WINDOW_SHOWN);
  if (engine->window == NULL) {
    trace_crash("SDL_CreateWindow Error: %s\n", SDL_GetError());
    engine_exit();
    exit(EXIT_FAILURE);
  }

  engine->render =
      SDL_CreateRenderer(engine->window, -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC |
                             SDL_RENDERER_TARGETTEXTURE);
  if (engine->render == NULL) {
    trace_crash("SDL_CreateRendetexturerer Error: %s\n", SDL_GetError());
    engine_exit();
    exit(EXIT_FAILURE);
  }

  int ww, wh;
  SDL_GetWindowSize(engine->window, &ww, &wh);
  SDL_SetRenderDrawColor(engine->render, 0x00, 0x00, 0x00,
                         SDL_ALPHA_TRANSPARENT);
  for (integer_t k = 0; k < LAYERS_SIZE; k++) {
    engine->layers[k] =
        SDL_CreateTexture(engine->render, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET, ww, wh);
    SDL_SetTextureBlendMode(engine->layers[k], SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(engine->render, engine->layers[k]);
    SDL_RenderClear(engine->render);
  }
  SDL_SetRenderTarget(engine->render, engine->layers[2]);

  if (TTF_Init() != 0) {
    trace_crash("TTF_Init Error: %s\n", SDL_GetError());
    engine_exit();
    exit(EXIT_FAILURE);
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    trace_crash("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                Mix_GetError());
    engine_exit();
    exit(EXIT_FAILURE);
  } else {
    Mix_WasInit = true;
  }
}

void engine_exit() {
  if (Mix_WasInit) {
    while (Mix_Init(0)) {
      Mix_Quit();
    }
    Mix_CloseAudio();
  }
  if (TTF_WasInit()) {
    TTF_Quit();
  }
  for (integer_t k = 0; k < LAYERS_SIZE; k++) {
    SDL_DestroyTexture(engine->layers[k]);
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
  assets_init();
  monitor_init();
  game_init();
  timing_init();

  SDL_Event event;

  // Main Loop
  while (engine->running) {
    // Events
    timing_perform();
    engine_process_events(&event);
    if (!engine->running) {
      break;
    }

    // Update
    while (timing_need_fixed_update()) {
      monitor_fps_increase();
      game_fixed_update(timing_get_delta_fixed_update());
      if (!engine->running) {
        break;
      }

      if (timing_need_delta_split()) {
        game_variable_update(timing_get_delta_fixed_update());
        if (!engine->running) {
          break;
        }
        timing_consumed_decrease();
      }
      timing_frame_accumulator_decrease();
    }
    if (!engine->running) {
      break;
    }
    game_variable_update(timing_calc_delta_variable_update());
    if (!engine->running) {
      break;
    }

    // Render
    SDL_SetRenderDrawColor(engine->render, 0x00, 0x00, 0x00,
                           SDL_ALPHA_TRANSPARENT);
    for (integer_t k = 0; k < LAYERS_SIZE; k++) {
      SDL_SetRenderTarget(engine->render, engine->layers[k]);
      SDL_RenderClear(engine->render);
    }

    SDL_SetRenderTarget(engine->render, engine->layers[2]);

    game_render(timing_calc_delta_render());
    monitor_fps_render();

    SDL_SetRenderTarget(engine->render, NULL);
    SDL_SetRenderDrawColor(engine->render, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(engine->render);

    for (integer_t k = 0; k < LAYERS_SIZE; k++) {
      SDL_RenderCopy(engine->render, engine->layers[k], NULL, NULL);
    }

    SDL_RenderPresent(engine->render);
  }

  // Exit
  game_exit();
  monitor_exit();
  assets_exit();
  engine_exit();
  return EXIT_SUCCESS;
}
