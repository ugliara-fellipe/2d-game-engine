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
#include "actor/player/control.h"

void control_init(control_t *control) {
  control->direction = v2d_zero;
  control->up = false;
  control->down = false;
  control->left = false;
  control->right = false;
  control->a = false;
  control->s = false;
  control->z = false;
  control->x = false;
  control->w = false;
}

void control_reset(control_t *control) { control_init(control); }

void control_process_events(control_t *control, SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      if (!control->up) {
        control->up = true;
      }
      break;
    case SDLK_DOWN:
      if (!control->down) {
        control->down = true;
      }
      break;
    case SDLK_LEFT:
      if (!control->left) {
        control->direction = v2d_add(control->direction, v2d_init(-1, 0));
        control->left = true;
      }
      break;
    case SDLK_RIGHT:
      if (!control->right) {
        control->direction = v2d_add(control->direction, v2d_init(1, 0));
        control->right = true;
      }
      break;
    case SDLK_a:
      control->a = true;
      break;
    case SDLK_s:
      control->s = true;
      break;
    case SDLK_z:
      if (!control->z) {
        control->direction = v2d_add(control->direction, v2d_init(0, -1));
        control->z = true;
      }
      break;
    case SDLK_x:
      control->x = true;
      break;
    case SDLK_w:
      control->w = true;
      break;
    }
  } else if (event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      if (control->up) {
        control->up = false;
      }
      break;
    case SDLK_DOWN:
      if (control->down) {
        control->down = false;
      }
      break;
    case SDLK_LEFT:
      if (control->left) {
        control->direction = v2d_sub(control->direction, v2d_init(-1, 0));
        control->left = false;
      }
      break;
    case SDLK_RIGHT:
      if (control->right) {
        control->direction = v2d_sub(control->direction, v2d_init(1, 0));
        control->right = false;
      }
      break;
    case SDLK_a:
      control->a = false;
      break;
    case SDLK_s:
      control->s = false;
      break;
    case SDLK_z:
      if (control->z) {
        control->direction = v2d_sub(control->direction, v2d_init(0, -1));
        control->z = false;
      }
      break;
    case SDLK_x:
      control->x = false;
      break;
    case SDLK_w:
      control->w = false;
      break;
    }
  }
}
