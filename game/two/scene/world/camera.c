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

#include "scene/world/camera.h"

static v2d_t limit;

static v2d_t world;
static v2d_t screen;

// Position of camere center in world
static v2d_t position;
static real_t zoom;

void camera_set(v2d_t screen_size, v2d_t world_size) {
  world = world_size;
  screen = screen_size;
  zoom = 1.0;
  limit = v2d_mult_sclr(screen, 0.5);
}

v2d_t camera_pos() { return position; }

v2d_t camera_size() { return screen; }

real_t camera_zoom() { return zoom; }

void camera_set_zoom(real_t value) {
  zoom = value;
}

static v2d_t camera_apply_zoom(v2d_t pivot, v2d_t point) {
  v2d_t move = v2d_sub(point, pivot);
  v2d_t zooming = v2d_mult_sclr(move, zoom);
  v2d_t back = v2d_add(zooming, v2d_mult_sclr(pivot, 1.0 /*zoom*/));
  return back;
}

v2d_t camera_zooming(v2d_t point) { return camera_apply_zoom(limit, point); }

void camera_move(v2d_t to) { position = to; }

v2d_t camera_screen_to_world(v2d_t pos) {
  // TODO: need be implemented
  return v2d_zero;
}

v2d_t camera_world_to_screen(v2d_t pos) {
  v2d_t result = v2d_add(limit, v2d_sub(pos, camera_pos()));
  return result;
}
