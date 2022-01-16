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

real_t fixed_deltatime;
integer_t desired_frametime;
integer_t frame_accumulator;
integer_t consumed_delta_time;

static integer_t vsync_maxerror;
static integer_t snap_frequencies[5];
static integer_t time_history_count;
static integer_t time_averager[4];
static integer_t prev_frame_time;
static integer_t delta_time;

static real_t timing_calc_fixed_deltatime() {
  return 1.0 / engine->update_rate;
}

static integer_t timing_calc_desired_frametime() {
  return SDL_GetPerformanceFrequency() / engine->update_rate;
}

static integer_t timing_calc_vsync_maxerror() {
  return SDL_GetPerformanceFrequency() * .0002;
}

static void timing_calc_snap_frequencies() {
  integer_t time_60hz = SDL_GetPerformanceFrequency() / 60;

  snap_frequencies[0] = time_60hz;           // 60fps
  snap_frequencies[1] = time_60hz * 2;       // 30fps
  snap_frequencies[2] = time_60hz * 3;       // 20fps
  snap_frequencies[3] = time_60hz * 4;       // 15fps
  snap_frequencies[4] = (time_60hz + 1) / 2; // 120fps
}

static void timing_init_averager() {
  time_history_count = 4;
  time_averager[0] = desired_frametime;
  time_averager[1] = desired_frametime;
  time_averager[2] = desired_frametime;
  time_averager[3] = desired_frametime;
}

static void timing_calc_frame_time() {
  integer_t current_frame_time = SDL_GetPerformanceCounter();
  delta_time = current_frame_time - prev_frame_time;
  prev_frame_time = current_frame_time;
}

static void timing_handle_unexpected_timer_anomalies() {
  if (delta_time > desired_frametime * 8) {
    delta_time = desired_frametime;
  }
  if (delta_time < 0) {
    delta_time = 0;
  }
}

static void timing_vsync_time_snapping() {
  for (integer_t index = 0; index < 5; index++) {
    integer_t snap = snap_frequencies[index];
    if (abs(delta_time - snap) < vsync_maxerror) {
      delta_time = snap;
      break;
    }
  }
}

static void timing_delta_time_averaging() {
  for (integer_t i = 0; i < time_history_count - 1; i++) {
    time_averager[i] = time_averager[i + 1];
  }
  time_averager[time_history_count - 1] = delta_time;
  delta_time = 0;
  for (integer_t i = 0; i < time_history_count; i++) {
    delta_time += time_averager[i];
  }
  delta_time /= time_history_count;
}

static void timing_spiral_of_death_protection() {
  if (frame_accumulator > desired_frametime * 8) {
    engine->timing_resync = true;
  }
}

static void timing_timer_resync() {
  if (engine->timing_resync) {
    frame_accumulator = 0;
    delta_time = desired_frametime;
    engine->timing_resync = false;
  }
}

void timing_init() {
  fixed_deltatime = timing_calc_fixed_deltatime();
  desired_frametime = timing_calc_desired_frametime();
  vsync_maxerror = timing_calc_vsync_maxerror();
  timing_calc_snap_frequencies();
  timing_init_averager();
  prev_frame_time = SDL_GetPerformanceCounter();
  frame_accumulator = 0;
}

void timing_perform() {
  timing_calc_frame_time();
  timing_handle_unexpected_timer_anomalies();
  timing_vsync_time_snapping();
  timing_delta_time_averaging();
  frame_accumulator += delta_time;
  timing_spiral_of_death_protection();
  timing_timer_resync();
  consumed_delta_time = delta_time;
}

void timing_consumed_decrease() { consumed_delta_time -= desired_frametime; }

void timing_frame_accumulator_decrease() {
  frame_accumulator -= desired_frametime;
}
