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

#include "toolbelt/shape.h"

point_t point_init(real_t x, real_t y) { return (point_t){x, y}; }

circle_t circle_init(real_t cx, real_t cy, real_t r) {
  return (circle_t){(v2d_t){cx, cy}, r};
}

rect_t rect_init(real_t ptlx, real_t ptly, real_t w, real_t h) {
  return (rect_t){(v2d_t){ptlx, ptly}, (v2d_t){w, h}};
}

line_t line_init(real_t p1x, real_t p1y, real_t p2x, real_t p2y) {
  return (line_t){(v2d_t){p1x, p1y}, (v2d_t){p2x, p2y}};
}
