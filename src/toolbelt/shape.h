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
  v2d_t c;  // position center
  real_t r; // radius
} circle_t;

typedef struct rect_s {
  v2d_t ptl; // position top left
  v2d_t s;   // size
} rect_t;

typedef struct line_s {
  v2d_t p1; // point one
  v2d_t p2; // point two
} line_t;

point_t point_init(real_t x, real_t y);

circle_t circle_init(real_t cx, real_t cy, real_t r);

rect_t rect_init(real_t ptlx, real_t ptly, real_t w, real_t h);

line_t line_init(real_t p1x, real_t p1y, real_t p2x, real_t p2y);

#endif
