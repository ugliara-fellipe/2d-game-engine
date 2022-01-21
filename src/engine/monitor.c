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

#include "engine/monitor.h"
#include "assets/assets.h"
#include "draw/text.h"
#include "engine/engine.h"
#include "toolbelt/trace.h"

static SDL_mutex *mutex_fps;
static integer_t fps = 0;
static SDL_TimerID fps_timer_id;
static integer_t fps_value_to_present = 0;

static Uint32 monitor_present_fps(Uint32 interval, void *param) {
  integer_t *fps_param = (integer_t *)param;
  if (SDL_LockMutex(mutex_fps) == 0) {
    fps_value_to_present = *fps_param;
    *fps_param = 0;
    SDL_UnlockMutex(mutex_fps);
  }
  return interval;
}

void monitor_init() {
  mutex_fps = SDL_CreateMutex();
  if (!mutex_fps) {
    trace_crash("Couldn't create mutex\n");
    engine_exit();
    exit(EXIT_FAILURE);
  }
  fps_timer_id = SDL_AddTimer(1000, monitor_present_fps, &fps);
}

void monitor_fps_render() {
  if (engine->show_fps) {
    draw_text(0, v2d_init(10, 10), v2d_init(80, 30), RGB_WHITE, "fps: %ld",
              fps_value_to_present);
  }
}

void monitor_fps_increase() {
  if (SDL_LockMutex(mutex_fps) == 0) {
    fps++;
    SDL_UnlockMutex(mutex_fps);
  }
}

void monitor_exit() {
  SDL_RemoveTimer(fps_timer_id);
  SDL_DestroyMutex(mutex_fps);
}

integer_t monitor_get_fps() { return fps_value_to_present; }
