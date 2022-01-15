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

#include "engine.h"
#include "game.h"
#include "toolbelt/trace.h"
#include <stdlib.h>

engine_t *engine = &(engine_t){.window = NULL,
                               .render = NULL,
                               .running = true,
                               .update_rate = 60,
                               .timing_resync = true,
                               .show_fps = true};

static TTF_Font *engine_font;

static void engine_init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    trace_crash("SDL_Init Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  engine->window =
      SDL_CreateWindow(game_name(), 100, 100, 800, 450, SDL_WINDOW_SHOWN);
  if (engine->window == NULL) {
    trace_crash("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  engine->render = SDL_CreateRenderer(
      engine->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (engine->render == NULL) {
    trace_crash("SDL_CreateRendetexturerer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  if (TTF_Init() != 0) {
    trace_crash("TTF_Init Error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(engine->render);
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  engine_font = TTF_OpenFont("assets/bgroveb.ttf", 24);
  if (engine_font == NULL) {
    trace_crash("Font not found, TTF_OpenFont\n");
    TTF_Quit();
    SDL_DestroyRenderer(engine->render);
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
}

static void engine_exit() {
  TTF_Quit();
  SDL_DestroyRenderer(engine->render);
  SDL_DestroyWindow(engine->window);
  SDL_Quit();
}

static void engine_process_events(SDL_Event *event) {
  while (SDL_PollEvent(event)) {
    game_process_events(event);
  }
}

static real_t timing_calc_fixed_deltatime() {
  return 1.0 / engine->update_rate;
}

static integer_t timing_calc_desired_frametime() {
  return SDL_GetPerformanceFrequency() / engine->update_rate;
}

static integer_t timing_calc_vsync_maxerror() {
  return SDL_GetPerformanceFrequency() * .0002;
}

static void timing_calc_snap_frequencies(integer_t *snap_frequencies) {
  integer_t time_60hz = SDL_GetPerformanceFrequency() / 60;

  snap_frequencies[0] = time_60hz;           // 60fps
  snap_frequencies[1] = time_60hz * 2;       // 30fps
  snap_frequencies[2] = time_60hz * 3;       // 20fps
  snap_frequencies[3] = time_60hz * 4;       // 15fps
  snap_frequencies[4] = (time_60hz + 1) / 2; // 120fps
}

static void timing_init_averager(integer_t *time_history_count,
                                 integer_t *time_averager,
                                 integer_t desired_frametime) {
  *time_history_count = 4;
  time_averager[0] = desired_frametime;
  time_averager[1] = desired_frametime;
  time_averager[2] = desired_frametime;
  time_averager[3] = desired_frametime;
}

static void timing_calc_frame_time(integer_t *delta_time,
                                   integer_t *prev_frame_time) {
  integer_t current_frame_time = SDL_GetPerformanceCounter();
  *delta_time = current_frame_time - *prev_frame_time;
  *prev_frame_time = current_frame_time;
}

static void
timing_handle_unexpected_timer_anomalies(integer_t *delta_time,
                                         integer_t desired_frametime) {
  if (*delta_time > desired_frametime * 8) {
    *delta_time = desired_frametime;
  }
  if (*delta_time < 0) {
    *delta_time = 0;
  }
}

static void timing_vsync_time_snapping(integer_t *delta_time,
                                       integer_t *snap_frequencies,
                                       integer_t vsync_maxerror) {
  for (integer_t index = 0; index < 5; index++) {
    integer_t snap = snap_frequencies[index];
    if (abs(*delta_time - snap) < vsync_maxerror) {
      *delta_time = snap;
      break;
    }
  }
}

static void timing_delta_time_averaging(integer_t *delta_time,
                                        integer_t time_history_count,
                                        integer_t *time_averager) {
  for (integer_t i = 0; i < time_history_count - 1; i++) {
    time_averager[i] = time_averager[i + 1];
  }
  time_averager[time_history_count - 1] = *delta_time;
  *delta_time = 0;
  for (integer_t i = 0; i < time_history_count; i++) {
    *delta_time += time_averager[i];
  }
  *delta_time /= time_history_count;
}

static void timing_spiral_of_death_protection(integer_t frame_accumulator,
                                              integer_t desired_frametime) {
  if (frame_accumulator > desired_frametime * 8) {
    engine->timing_resync = true;
  }
}

static void timing_timer_resync(integer_t *frame_accumulator,
                                integer_t *delta_time,
                                integer_t desired_frametime) {
  if (engine->timing_resync) {
    *frame_accumulator = 0;
    *delta_time = desired_frametime;
    engine->timing_resync = false;
  }
}

static SDL_mutex *mutex_fps_monitor;
static integer_t fps_monitor = 0;
static SDL_TimerID fps_monitor_timer_id;
static integer_t fps_value_to_present = 0;

static Uint32 engine_present_fps(Uint32 interval, void *param) {
  integer_t *fps_monitor = (integer_t *)param;
  if (SDL_LockMutex(mutex_fps_monitor) == 0) {
    fps_value_to_present = *fps_monitor;
    *fps_monitor = 0;
    SDL_UnlockMutex(mutex_fps_monitor);
  }
  return interval;
}

static void engine_fps_monitor_init() {
  mutex_fps_monitor = SDL_CreateMutex();
  if (!mutex_fps_monitor) {
    trace_crash("Couldn't create mutex\n");
    SDL_DestroyRenderer(engine->render);
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  fps_monitor_timer_id = SDL_AddTimer(1000, engine_present_fps, &fps_monitor);
}

static void engine_fps_render() {
  if (engine->show_fps) {
    SDL_Color white = {255, 255, 255};
    char msg[10];
    sprintf(msg, "fps: %ld", fps_value_to_present);
    SDL_Surface *surface_message =
        TTF_RenderText_Solid(engine_font, msg, white);
    SDL_Texture *message =
        SDL_CreateTextureFromSurface(engine->render, surface_message);
    SDL_Rect message_rect;
    message_rect.x = 10;
    message_rect.y = 10;
    message_rect.w = 110;
    message_rect.h = 50;
    SDL_RenderCopy(engine->render, message, NULL, &message_rect);
    SDL_FreeSurface(surface_message);
    SDL_DestroyTexture(message);
  }
}

static void engine_fps_monitor_increase() {
  if (SDL_LockMutex(mutex_fps_monitor) == 0) {
    fps_monitor++;
    SDL_UnlockMutex(mutex_fps_monitor);
  }
}

static void engine_fps_monitor_exit() {
  SDL_RemoveTimer(fps_monitor_timer_id);
  SDL_DestroyMutex(mutex_fps_monitor);
}

int main(int argc, char *argv[]) {
  engine_init();

  engine_fps_monitor_init();

  game_init();

  real_t fixed_deltatime = timing_calc_fixed_deltatime();
  integer_t desired_frametime = timing_calc_desired_frametime();

  integer_t vsync_maxerror = timing_calc_vsync_maxerror();

  integer_t snap_frequencies[5];
  timing_calc_snap_frequencies(snap_frequencies);

  integer_t time_history_count;
  integer_t time_averager[4];
  timing_init_averager(&time_history_count, time_averager, desired_frametime);

  integer_t prev_frame_time = SDL_GetPerformanceCounter();
  integer_t frame_accumulator = 0;

  SDL_Event event;

  while (engine->running) {

    integer_t delta_time;
    timing_calc_frame_time(&delta_time, &prev_frame_time);

    timing_handle_unexpected_timer_anomalies(&delta_time, desired_frametime);

    timing_vsync_time_snapping(&delta_time, snap_frequencies, vsync_maxerror);

    timing_delta_time_averaging(&delta_time, time_history_count, time_averager);
    frame_accumulator += delta_time;

    timing_spiral_of_death_protection(frame_accumulator, desired_frametime);

    timing_timer_resync(&frame_accumulator, &delta_time, desired_frametime);

    engine_process_events(&event);

    integer_t consumedDeltaTime = delta_time;

    while (frame_accumulator >= desired_frametime) {
      game_fixed_update(fixed_deltatime);

      if (consumedDeltaTime > desired_frametime) {
        game_variable_update(fixed_deltatime);
        consumedDeltaTime -= desired_frametime;
      }

      frame_accumulator -= desired_frametime;
    }

    game_variable_update((real_t)consumedDeltaTime /
                         SDL_GetPerformanceFrequency());

    SDL_RenderClear(engine->render);
    game_render((real_t)frame_accumulator / desired_frametime);
    engine_fps_render();
    SDL_RenderPresent(engine->render);
    engine_fps_monitor_increase();
  }

  game_exit();

  engine_fps_monitor_exit();

  engine_exit();

  return EXIT_SUCCESS;
}