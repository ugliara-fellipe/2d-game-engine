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

#include "actor/trajectory.h"
#include "scene/world/camera.h"

void trajectory_init(trajectory_t *trajectory, point_t point) {
  for (integer_t index = 0; index < TRAJECTORY_HISTORY; index++) {
    trajectory->move_array[index] = point;
  }
  trajectory->move_index = 0;
}

void trajectory_update(trajectory_t *trajectory, point_t point) {
  if (trajectory->move_index < TRAJECTORY_HISTORY) {
    trajectory->move_array[trajectory->move_index] = point;
    trajectory->move_index++;
  } else {
    trajectory->move_index = 0;
  }
}

void trajectory_render(trajectory_t *trajectory) {
  Sint16 array_x[TRAJECTORY_HISTORY];
  Sint16 array_y[TRAJECTORY_HISTORY];

  integer_t index_array = 0;

  for (integer_t k = trajectory->move_index; k < TRAJECTORY_HISTORY; k++) {
    v2d_t pos = camera_world_to_screen(trajectory->move_array[k]);
    pos = camera_zooming(pos);
    array_x[index_array] = pos.x;
    array_y[index_array] = pos.y;
    index_array++;
  }

  for (integer_t j = 0; j < trajectory->move_index; j++) {
    v2d_t pos = camera_world_to_screen(trajectory->move_array[j]);
    pos = camera_zooming(pos);
    array_x[index_array] = pos.x;
    array_y[index_array] = pos.y;
    index_array++;
  }

  // iterator of amounts
  const integer_t amount = 30;
  const integer_t bezier_interpolation = 10;
  for (integer_t t = 0; t < TRAJECTORY_HISTORY; t += (amount - 1)) {

    // build a new amount
    Sint16 x[amount];
    Sint16 y[amount];

    for (integer_t p = 0; p < amount; p++) {
      if (t + p >= TRAJECTORY_HISTORY) {
        x[p] = array_x[TRAJECTORY_HISTORY - 1];
        y[p] = array_y[TRAJECTORY_HISTORY - 1];
      } else {
        x[p] = array_x[t + p];
        y[p] = array_y[t + p];
      }
    }

    // Draw amount
    bezierRGBA(engine->render, x, y, amount, bezier_interpolation, RGB_WHITE.r,
               RGB_WHITE.g, RGB_WHITE.b, RGB_WHITE.a);
  }
}
