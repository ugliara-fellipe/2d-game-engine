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

#ifndef SHAPES_H
#define SHAPES_H

#include "toolbelt/vector2d.h"

typedef v2d_t point_t;

typedef struct circle_s {
  v2d_t pos_center;
  real_t radius;
} circle_t;

typedef struct rect_s {
  v2d_t pos_top_left;
  v2d_t size;
} rect_t;

typedef struct line_s {
  v2d_t pos_one;
  v2d_t pos_two;
} line_t;

point_t point_init(real_t x, real_t y);

circle_t circle_init(real_t x_center, real_t y_center, real_t radius);

rect_t rect_init(real_t x_top_left, real_t y_top_left, real_t width,
                       real_t height);

line_t line_init(real_t x_pos_one, real_t y_pos_one, real_t x_pos_two,
                       real_t y_pos_two);

#endif
