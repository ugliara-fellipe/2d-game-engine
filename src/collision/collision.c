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
  real_t distance = v2d_dist(p, c.pos_center);

  if (distance <= c.radius) {
    return true;
  }
  return false;
}

bool collision_circle_circle(circle_t c1, circle_t c2) {
  real_t distance = v2d_dist(c1.pos_center, c2.pos_center);

  if (distance <= c1.radius + c2.radius) {
    return true;
  }
  return false;
}

bool collision_point_rect(point_t p, rect_t r) {
  if (p.x >= r.pos_top_left.x && p.x <= r.pos_top_left.x + r.size.x &&
      p.y >= r.pos_top_left.y && p.y <= r.pos_top_left.y + r.size.y) {
    return true;
  }
  return false;
}

bool collision_rect_rect(rect_t r1, rect_t r2) {
  if (r1.pos_top_left.x + r1.size.x >= r2.pos_top_left.x &&
      r1.pos_top_left.x <= r2.pos_top_left.x + r2.size.x &&
      r1.pos_top_left.y + r1.size.y >= r2.pos_top_left.y &&
      r1.pos_top_left.y <= r2.pos_top_left.y + r2.size.y) {
    return true;
  }
  return false;
}

bool collision_circle_rect(circle_t c, rect_t r) {
  v2d_t test = c.pos_center;

  if (c.pos_center.x < r.pos_top_left.x) {
    test.x = r.pos_top_left.x;
  } else if (c.pos_center.x > r.pos_top_left.x + r.size.x) {
    test.x = r.pos_top_left.x + r.size.x;
  }
  if (c.pos_center.y < r.pos_top_left.y) {
    test.y = r.pos_top_left.y;
  } else if (c.pos_center.y > r.pos_top_left.y + r.size.y) {
    test.y = r.pos_top_left.y + r.size.y;
  }

  real_t distance = v2d_dist(c.pos_center, test);

  if (distance <= c.radius) {
    return true;
  }
  return false;
}

bool collision_line_point(line_t l, point_t p) {
  real_t d1 = v2d_dist(p, l.pos_one);
  real_t d2 = v2d_dist(p, l.pos_two);

  real_t line_length = v2d_dist(l.pos_one, l.pos_two);

  real_t buffer = 0.1;

  if (d1 + d2 >= line_length - buffer && d1 + d2 <= line_length + buffer) {
    return true;
  }
  return false;
}

bool collision_line_circle(line_t l, circle_t c) {
  bool inside1 = collision_point_circle(l.pos_one, c);
  bool inside2 = collision_point_circle(l.pos_two, c);
  if (inside1 || inside2) {
    return true;
  }

  real_t len = v2d_dist(l.pos_one, l.pos_two);

  v2d_t dot_tmp =
      v2d_mult(v2d_sub(c.pos_center, l.pos_one), v2d_sub(l.pos_two, l.pos_one));
  real_t dot = (dot_tmp.x + dot_tmp.y) / (len * len);

  v2d_t closest =
      v2d_add(l.pos_one, v2d_mult_sclr(v2d_sub(l.pos_two, l.pos_one), dot));

  bool on_segment = collision_line_point(l, closest);
  if (!on_segment) {
    return false;
  }

  real_t distance = v2d_dist(closest, c.pos_center);

  if (distance <= c.radius) {
    return true;
  }
  return false;
}

bool collision_line_line(line_t l1, line_t l2) {
  v2d_t l1_sub = v2d_sub(l1.pos_two, l1.pos_one);
  v2d_t l2_sub = v2d_sub(l2.pos_two, l2.pos_one);
  v2d_t one_sub = v2d_sub(l1.pos_one, l2.pos_one);

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
  bool left = collision_line_line(
      l, line_init(r.pos_top_left.x, r.pos_top_left.y, r.pos_top_left.x,
                   r.pos_top_left.y + r.size.y));
  bool right = collision_line_line(
      l, line_init(r.pos_top_left.x + r.size.x, r.pos_top_left.y,
                   r.pos_top_left.x + r.size.x, r.pos_top_left.y + r.size.y));
  bool top = collision_line_line(
      l, line_init(r.pos_top_left.x, r.pos_top_left.y,
                   r.pos_top_left.x + r.size.x, r.pos_top_left.y));
  bool bottom = collision_line_line(
      l, line_init(r.pos_top_left.x, r.pos_top_left.y + r.size.y,
                   r.pos_top_left.x + r.size.x, r.pos_top_left.y + r.size.y));

  if (left || right || top || bottom) {
    return true;
  }
  return false;
}
