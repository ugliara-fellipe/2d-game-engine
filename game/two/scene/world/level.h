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

#ifndef LEVEL_H
#define LEVEL_H

#include "game.h"

typedef enum {
  REPEL_UP,
  REPEL_DOWN,
  REPEL_LEFT,
  REPEL_RIGHT,
  REPEL_PLATFORM
} line_repel_e;

typedef struct level_line_s {
  line_t line;
  line_repel_e repel;
} level_line_t;

typedef struct level_s {
  level_line_t *map;
  integer_t map_size;
} level_t;

entity_t *level_init(integer_t amount, integer_t nodes_amount);

void level_line(entity_t *level, integer_t index, line_t line,
                line_repel_e repel);

void level_matrix(entity_t *level, char **matrix, integer_t w, integer_t h,
                  real_t s);

v2d_t level_collision_update(level_t *level, rect_t rect, v2d_t direction,
                             v2d_t speed, real_t gravity);

bool level_is_on_floor(level_t *level, rect_t body);

bool level_is_on_celling(level_t *level, rect_t body);

bool level_is_on_platform(level_t *level, rect_t body);

#endif
