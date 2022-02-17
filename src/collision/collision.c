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

#include "collision/collision.h"

bool collision_point_point(point_t p1, point_t p2) {
  if (p1.x == p2.x && p1.y == p2.y) {
    return true;
  }
  return false;
}

bool collision_point_circle(point_t p, circle_t c) {
  real_t distance = v2d_dist(p, c.c);

  if (distance <= c.r) {
    return true;
  }
  return false;
}

bool collision_circle_circle(circle_t c1, circle_t c2) {
  real_t distance = v2d_dist(c1.c, c2.c);

  if (distance <= c1.r + c2.r) {
    return true;
  }
  return false;
}

bool collision_point_rect(point_t p, rect_t r) {
  if (p.x >= r.ptl.x && p.x <= r.ptl.x + r.s.x && p.y >= r.ptl.y &&
      p.y <= r.ptl.y + r.s.y) {
    return true;
  }
  return false;
}

bool collision_rect_rect(rect_t r1, rect_t r2) {
  if (r1.ptl.x + r1.s.x >= r2.ptl.x && r1.ptl.x <= r2.ptl.x + r2.s.x &&
      r1.ptl.y + r1.s.y >= r2.ptl.y && r1.ptl.y <= r2.ptl.y + r2.s.y) {
    return true;
  }
  return false;
}

bool collision_circle_rect(circle_t c, rect_t r) {
  v2d_t test = c.c;

  if (c.c.x < r.ptl.x) {
    test.x = r.ptl.x;
  } else if (c.c.x > r.ptl.x + r.s.x) {
    test.x = r.ptl.x + r.s.x;
  }
  if (c.c.y < r.ptl.y) {
    test.y = r.ptl.y;
  } else if (c.c.y > r.ptl.y + r.s.y) {
    test.y = r.ptl.y + r.s.y;
  }

  real_t distance = v2d_dist(c.c, test);

  if (distance <= c.r) {
    return true;
  }
  return false;
}

bool collision_line_point(line_t l, point_t p) {
  real_t d1 = v2d_dist(p, l.p1);
  real_t d2 = v2d_dist(p, l.p2);

  real_t line_length = v2d_dist(l.p1, l.p2);

  real_t buffer = 0.1;

  if (d1 + d2 >= line_length - buffer && d1 + d2 <= line_length + buffer) {
    return true;
  }
  return false;
}

bool collision_line_circle(line_t l, circle_t c) {
  bool inside1 = collision_point_circle(l.p1, c);
  bool inside2 = collision_point_circle(l.p2, c);
  if (inside1 || inside2) {
    return true;
  }

  real_t len = v2d_dist(l.p1, l.p2);

  v2d_t dot_tmp = v2d_mult(v2d_sub(c.c, l.p1), v2d_sub(l.p2, l.p1));
  real_t dot = (dot_tmp.x + dot_tmp.y) / (len * len);

  v2d_t closest = v2d_add(l.p1, v2d_mult_sclr(v2d_sub(l.p2, l.p1), dot));

  bool on_segment = collision_line_point(l, closest);
  if (!on_segment) {
    return false;
  }

  real_t distance = v2d_dist(closest, c.c);

  if (distance <= c.r) {
    return true;
  }
  return false;
}

bool collision_line_line(line_t l1, line_t l2) {
  v2d_t l1_sub = v2d_sub(l1.p2, l1.p1);
  v2d_t l2_sub = v2d_sub(l2.p2, l2.p1);
  v2d_t one_sub = v2d_sub(l1.p1, l2.p1);

  real_t ua = ((l2_sub.x) * (one_sub.y) - (l2_sub.y) * (one_sub.x)) /
              ((l2_sub.y) * (l1_sub.x) - (l2_sub.x) * (l1_sub.y));

  real_t ub = ((l1_sub.x) * (one_sub.y) - (l1_sub.y) * (one_sub.x)) /
              ((l2_sub.y) * (l1_sub.x) - (l2_sub.x) * (l1_sub.y));

  if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
    return true;
  }
  return false;
}

bool collision_line_rect(line_t l, rect_t r) {
  real_t xw = r.ptl.x + r.s.x;
  real_t yh = r.ptl.y + r.s.y;

  bool left = collision_line_line(l, line_init(r.ptl.x, r.ptl.y, r.ptl.x, yh));
  bool right = collision_line_line(l, line_init(xw, r.ptl.y, xw, yh));
  bool top = collision_line_line(l, line_init(r.ptl.x, r.ptl.y, xw, r.ptl.y));
  bool bottom = collision_line_line(l, line_init(r.ptl.x, yh, xw, yh));

  bool p1_inside = collision_point_rect(l.p1, r);
  bool p2_inside = collision_point_rect(l.p2, r);

  if (left || right || top || bottom || p1_inside || p2_inside) {
    return true;
  }
  return false;
}
