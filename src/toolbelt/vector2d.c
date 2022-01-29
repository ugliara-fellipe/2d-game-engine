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

#include "toolbelt/vector2d.h"

v2d_t v2d_zero = {0.0f, 0.0f};

v2d_t v2d_one = {1.0f, 1.0f};

v2d_t v2d_init(const real_t x, const real_t y) { return (v2d_t){x, y}; }

bool v2d_equal(v2d_t v1, v2d_t v2) { return (v1.x == v2.x && v1.y == v2.y); }

v2d_t v2d_add(v2d_t v1, v2d_t v2) { return v2d_init(v1.x + v2.x, v1.y + v2.y); }

v2d_t v2d_sub(v2d_t v1, v2d_t v2) { return v2d_init(v1.x - v2.x, v1.y - v2.y); }

v2d_t v2d_neg(v2d_t v) { return v2d_init(-v.x, -v.y); }

v2d_t v2d_mult(v2d_t v, real_t s) { return v2d_init(v.x * s, v.y * s); }

real_t v2d_dot(v2d_t v1, v2d_t v2) { return (v1.x * v2.x + v1.y * v2.y); }

real_t v2d_cross(v2d_t v1, v2d_t v2) { return (v1.x * v2.y - v1.y * v2.x); }

v2d_t v2d_perp(v2d_t v) { return v2d_init(-v.y, v.x); }

v2d_t v2d_rperp(v2d_t v) { return v2d_init(v.y, -v.x); }

v2d_t v2d_project(v2d_t v1, v2d_t v2) {
  return v2d_mult(v2, v2d_dot(v1, v2) / v2d_dot(v2, v2));
}

v2d_t v2d_forangle(real_t a) { return v2d_init(cos(a), sin(a)); }

real_t v2d_toangle(v2d_t v) { return atan2(v.y, v.x); }

v2d_t v2d_rotate(v2d_t v1, v2d_t v2) {
  return v2d_init(v1.x * v2.x - v1.y * v2.y, v1.x * v2.y + v1.y * v2.x);
}

v2d_t v2d_unrotate(v2d_t v1, v2d_t v2) {
  return v2d_init(v1.x * v2.x + v1.y * v2.y, v1.y * v2.x - v1.x * v2.y);
}

real_t v2d_lengthsq(v2d_t v) { return v2d_dot(v, v); }

real_t v2d_length(v2d_t v) { return sqrt(v2d_dot(v, v)); }

v2d_t v2d_lerp(v2d_t v1, v2d_t v2, real_t t) {
  return v2d_add(v2d_mult(v1, 1.0f - t), v2d_mult(v2, t));
}

v2d_t v2d_normalize(v2d_t v) {
  // Neat trick I saw somewhere to avoid div/0
  return v2d_mult(v, 1.0f / (v2d_length(v) + DBL_MIN));
}

v2d_t v2d_slerp(v2d_t v1, v2d_t v2, real_t t) {
  real_t dot = v2d_dot(v2d_normalize(v1), v2d_normalize(v2));
  real_t omega = acos(math_clamp(dot, -1.0f, 1.0f));

  if (omega < 1e-3) {
    return v2d_lerp(v1, v2, t);
  } else {
    real_t denom = 1.0f / sin(omega);
    return v2d_add(v2d_mult(v1, sin((1.0f - t) * omega) * denom),
                   v2d_mult(v2, sin(t * omega) * denom));
  }
}

v2d_t v2d_slerpconst(v2d_t v1, v2d_t v2, real_t a) {
  real_t dot = v2d_dot(v2d_normalize(v1), v2d_normalize(v2));
  real_t omega = acos(math_clamp(dot, -1.0f, 1.0f));

  return v2d_slerp(v1, v2, math_min(a, omega) / omega);
}

v2d_t v2d_clamp(v2d_t v, real_t len) {
  return (v2d_dot(v, v) > len * len) ? v2d_mult(v2d_normalize(v), len) : v;
}

v2d_t v2d_lerpconst(v2d_t v1, v2d_t v2, real_t d) {
  return v2d_add(v1, v2d_clamp(v2d_sub(v2, v1), d));
}

real_t v2d_dist(v2d_t v1, v2d_t v2) { return v2d_length(v2d_sub(v1, v2)); }

real_t v2d_distsq(v2d_t v1, v2d_t v2) { return v2d_lengthsq(v2d_sub(v1, v2)); }

bool v2d_near(v2d_t v1, v2d_t v2, real_t dist) {
  return v2d_distsq(v1, v2) < dist * dist;
}
