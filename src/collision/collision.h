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

#ifndef COLLISION_H
#define COLLISION_H

#include "toolbelt/shape.h"
#include "toolbelt/vector2d.h"

bool collision_point_point(point_t p1, point_t p2);
bool collision_point_circle(point_t p, circle_t c);
bool collision_circle_circle(circle_t c1, circle_t c2);
bool collision_point_rect(point_t p, rect_t r);
bool collision_rect_rect(rect_t r1, rect_t r2);
bool collision_circle_rect(circle_t c, rect_t r);
bool collision_line_point(line_t l, point_t p);
bool collision_line_circle(line_t l, circle_t c);
bool collision_line_line(line_t l1, line_t l2);
bool collision_line_rect(line_t l, rect_t r);

#endif
