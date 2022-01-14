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

#include "toolbelt/maths.h"

real_t math_max(real_t a, real_t b) { return (a > b) ? a : b; }

real_t math_min(real_t a, real_t b) { return (a < b) ? a : b; }

real_t math_abs(real_t n) { return (n < 0) ? -n : n; }

real_t math_clamp(real_t n, real_t min_value, real_t max_value) {
  return math_min(math_max(n, min_value), max_value);
}

real_t math_lerp(real_t n1, real_t n2, real_t t) {
  return n1 * (1.0f - t) + n2 * t;
}

real_t math_lerpconst(real_t n1, real_t n2, real_t d) {
  return n1 + math_clamp(n2 - n1, -d, d);
}
