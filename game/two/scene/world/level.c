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

#include "scene/world/level.h"
#include "actor/player/player.h"
#include "scene/world/camera.h"

static void render(entity_t *entity, sec_t delta) {
  level_t *level = entity->aspect->context;
  for (int index = 0; index < level->map_size; index++) {
    v2d_t p1 =
        camera_zooming(camera_world_to_screen(level->map[index].line.p1));
    v2d_t p2 =
        camera_zooming(camera_world_to_screen(level->map[index].line.p2));
    line_t line = line_init(p1.x, p1.y, p2.x, p2.y);
    line_draw(line, RGB_WHITE);
  }
}

static void finish(void *context) {
  level_t *level = context;
  free(level->map);
}

entity_t *level_init(integer_t amount, integer_t nodes_amount) {
  entity_t *level = entity_init(nodes_amount);
  level->aspect = aspect_init();

  level_t *context = calloc(1, sizeof(level_t));
  context->map = calloc(amount, sizeof(level_line_t));
  context->map_size = amount;

  level->aspect->context = context;
  level->aspect->render = render;
  level->aspect->finish = finish;

  return level;
}

void level_line(entity_t *level, integer_t index, line_t line,
                line_repel_e repel) {
  level_t *context = level->aspect->context;

  context->map[index].line = line;
  context->map[index].repel = repel;
}

void level_matrix(entity_t *level, char **matrix, integer_t w, integer_t h,
                  real_t s) {
  integer_t index = 0;

  for (integer_t i = 0; i < h; i++) {
    integer_t begin = -1;
    integer_t end = -1;
    char repel = '?';
    for (integer_t j = 0; j < w; j++) {

      if (repel == 'C' && (matrix[i][j] != repel || j == w - 1)) {
        if (j == w - 1) {
          level_line(level, index,
                     line_init(begin * s, i * s, (end + 1) * s, i * s),
                     REPEL_DOWN);
        } else {
          level_line(level, index, line_init(begin * s, i * s, end * s, i * s),
                     REPEL_DOWN);
        }
        index++;
        begin = -1;
        end = -1;
        repel = '?';
      }

      if (repel == 'F' && (matrix[i][j] != repel || j == w - 1)) {
        if (j == w - 1) {
          level_line(level, index,
                     line_init(begin * s, i * s, (end + 1) * s, i * s),
                     REPEL_UP);
        } else {
          level_line(level, index, line_init(begin * s, i * s, end * s, i * s),
                     REPEL_UP);
        }
        index++;
        begin = -1;
        end = -1;
        repel = '?';
      }

      if (repel == 'P' && (matrix[i][j] != repel || j == w - 1)) {
        level_line(level, index,
                   line_init((begin - 1) * s, i * s, (end + 1) * s, i * s),
                   REPEL_PLATFORM);
        index++;
        begin = -1;
        end = -1;
        repel = '?';
      }

      if (matrix[i][j] == 'C') {
        if (begin == -1) {
          begin = j;
          end = j;
          repel = 'C';
        } else {
          end = j;
        }
      }

      if (matrix[i][j] == 'F') {
        if (begin == -1) {
          begin = j;
          end = j;
          repel = 'F';
        } else {
          end = j;
        }
      }

      if (matrix[i][j] == 'P') {
        if (begin == -1) {
          begin = j;
          end = j;
          repel = 'P';
        } else {
          end = j;
        }
      }
    }
  }

  for (integer_t i = 0; i < w; i++) {
    integer_t begin = -1;
    integer_t end = -1;
    char repel = '?';
    for (integer_t j = 0; j < h; j++) {

      if (repel == 'L' && (matrix[j][i] != repel || j == h - 1)) {
        level_line(level, index, line_init(i * s, begin * s, i * s, end * s),
                   REPEL_RIGHT);
        index++;
        begin = -1;
        end = -1;
        repel = '?';
      }

      if (repel == 'R' && (matrix[j][i] != repel || j == h - 1)) {
        level_line(level, index, line_init(i * s, begin * s, i * s, end * s),
                   REPEL_LEFT);
        index++;
        begin = -1;
        end = -1;
        repel = '?';
      }

      if (matrix[j][i] == 'L') {
        if (begin == -1) {
          begin = j - 1;
          end = j + 1;
          repel = 'L';
        } else {
          end = j + 1;
        }
      }

      if (matrix[j][i] == 'R') {
        if (begin == -1) {
          begin = j - 1;
          end = j + 1;
          repel = 'R';
        } else {
          end = j + 1;
        }
      }
    }
  }
}

v2d_t level_collision_update(level_t *level, rect_t body, v2d_t direction,
                             v2d_t speed, real_t gravity) {
  v2d_t result = body.ptl;
  v2d_t original_direction = direction;

  bool apply_gravity = true;
  real_t adjust = 2;
  real_t up_down_ajust = 4;
  real_t line_check_dst = 15;
  real_t line_border_near = 6;

  // Perform Level Collisions
  for (integer_t index = 0; index < level->map_size; index++) {
    if (collision_line_rect(level->map[index].line, body)) {
      if (level->map[index].repel == REPEL_UP ||
          level->map[index].repel == REPEL_PLATFORM) {
        // Edge check
        real_t rp = body.ptl.x + body.s.x; // most right player point
        real_t ll =
            math_min(level->map[index].line.p1.x,
                     level->map[index].line.p2.x); // most left line point
        if (rp < ll + adjust) {
          continue;
        }
        real_t lp = body.ptl.x;
        real_t rl =
            math_max(level->map[index].line.p1.x, level->map[index].line.p2.x);
        if (rl < lp + adjust) {
          continue;
        }

        rect_t rect_check = rect_init(
            (body.ptl.x) - (body.s.x / up_down_ajust),
            (body.ptl.y) + ((up_down_ajust - 1) * body.s.y / up_down_ajust),
            body.s.x + (2 * (body.s.x / up_down_ajust)),
            (2 * (body.s.y / up_down_ajust)));
        if (collision_line_rect(level->map[index].line, rect_check)) {
          // Perform floor collision
          apply_gravity = false;
          result.y = level->map[index].line.p1.y - body.s.y;
        }
      }
      if (level->map[index].repel == REPEL_DOWN) {
        // Edge check
        real_t rp = body.ptl.x + body.s.x; // most right player point
        real_t ll =
            math_min(level->map[index].line.p1.x,
                     level->map[index].line.p2.x); // most left line point
        if (rp < ll + adjust) {
          continue;
        }
        real_t lp = body.ptl.x;
        real_t rl =
            math_max(level->map[index].line.p1.x, level->map[index].line.p2.x);
        if (rl < lp + adjust) {
          continue;
        }

        rect_t rect_check =
            rect_init((body.ptl.x) - (body.s.x / up_down_ajust),
                      (body.ptl.y) - (body.s.y / up_down_ajust),
                      body.s.x + (2 * (body.s.x / up_down_ajust)),
                      (2 * (body.s.y / up_down_ajust)));
        if (collision_line_rect(level->map[index].line, rect_check)) {
          // Perform Celinig Collision
          direction.y = 0;
          result.y = level->map[index].line.p1.y;
        }
      }
      if (level->map[index].repel == REPEL_RIGHT && direction.x == -1) {
        // Edge check
        real_t bp = body.ptl.y + body.s.y; // most botton player point
        real_t tl =
            math_min(level->map[index].line.p1.y,
                     level->map[index].line.p2.y); // most top line point
        if (bp < tl + adjust) {
          continue;
        }
        real_t tp = body.ptl.y; // most top player point
        real_t bl =
            math_max(level->map[index].line.p1.y,
                     level->map[index].line.p2.y); // most botton line point
        if (bl < tp + adjust) {
          continue;
        }

        // Check vertical near line
        line_t line_check_1 =
            line_init(body.ptl.x - line_check_dst,
                      body.ptl.y + (body.s.y / line_border_near),
                      body.ptl.x + line_check_dst,
                      body.ptl.y + (body.s.y / line_border_near));
        line_t line_check_2 = line_init(
            body.ptl.x - line_check_dst,
            body.ptl.y + ((line_border_near - 1) * body.s.y / line_border_near),
            body.ptl.x + line_check_dst,
            body.ptl.y +
                ((line_border_near - 1) * body.s.y / line_border_near));
        circle_t circle_check = circle_init(
            body.ptl.x, body.ptl.y + (body.s.y / 2), line_check_dst);

        if (collision_line_line(level->map[index].line, line_check_1) ||
            collision_line_line(level->map[index].line, line_check_2) ||
            collision_line_circle(level->map[index].line, circle_check)) {
          // Perform Left Collision
          direction.x = 0;
          result.x = level->map[index].line.p1.x;
        }
      }
      if (level->map[index].repel == REPEL_LEFT && direction.x == 1) {
        // Edge check
        real_t bp = body.ptl.y + body.s.y;
        real_t tl =
            math_min(level->map[index].line.p1.y, level->map[index].line.p2.y);
        if (bp < tl + adjust) {
          continue;
        }
        real_t tp = body.ptl.y;
        real_t bl =
            math_max(level->map[index].line.p1.y, level->map[index].line.p2.y);
        if (bl < tp + adjust) {
          continue;
        }

        // Check vertical near line
        line_t line_check_1 =
            line_init(body.ptl.x + body.s.x - line_check_dst,
                      body.ptl.y + (body.s.y / line_border_near),
                      body.ptl.x + body.s.x + line_check_dst,
                      body.ptl.y + (body.s.y / line_border_near));
        line_t line_check_2 = line_init(
            body.ptl.x + body.s.x - line_check_dst,
            body.ptl.y + ((line_border_near - 1) * body.s.y / line_border_near),
            body.ptl.x + body.s.x + line_check_dst,
            body.ptl.y +
                ((line_border_near - 1) * body.s.y / line_border_near));
        circle_t circle_check = circle_init(
            body.ptl.x + body.s.x, body.ptl.y + (body.s.y / 2), line_check_dst);
        if (collision_line_line(level->map[index].line, line_check_1) ||
            collision_line_line(level->map[index].line, line_check_2) ||
            collision_line_circle(level->map[index].line, circle_check)) {
          // Perform Right Collision
          direction.x = 0;
          result.x = level->map[index].line.p1.x - body.s.x;
        }
      }
    }
  }

  if (apply_gravity && direction.y == 0 && original_direction.y == 0) {
    direction.y = 1;
    speed.y = gravity;
  }

  return v2d_add(result, v2d_mult(direction, speed));
}

bool level_is_on_floor(level_t *level, rect_t body) {
  real_t up_down_ajust = 4;
  real_t edges_ajust = 10;
  rect_t rect_check =
      rect_init((body.ptl.x) + (body.s.x / edges_ajust),
                (body.ptl.y) + ((up_down_ajust - 1) * body.s.y / up_down_ajust),
                body.s.x - (2 * (body.s.x / edges_ajust)),
                (1.1 * (body.s.y / up_down_ajust)));
  for (integer_t index = 0; index < level->map_size; index++) {
    if (collision_line_rect(level->map[index].line, rect_check)) {
      if (level->map[index].repel == REPEL_UP) {
        return true;
      }
    }
  }
  return false;
}

bool level_is_on_celling(level_t *level, rect_t body) {
  real_t up_down_ajust = 4;
  real_t edges_ajust = 20;
  rect_t rect_check =
      rect_init((body.ptl.x) + (body.s.x / edges_ajust),
                (body.ptl.y) - (0.1 * (body.s.y / up_down_ajust)),
                body.s.x - (2 * (body.s.x / edges_ajust)),
                (1.1 * (body.s.y / up_down_ajust)));
  for (integer_t index = 0; index < level->map_size; index++) {
    if (collision_line_rect(level->map[index].line, rect_check)) {
      if (level->map[index].repel == REPEL_DOWN) {
        return true;
      }
    }
  }
  return false;
}

bool level_is_on_platform(level_t *level, rect_t body) {
  real_t up_down_ajust = 4;
  real_t edges_ajust = 10;
  rect_t rect_check =
      rect_init((body.ptl.x) + (body.s.x / edges_ajust),
                (body.ptl.y) + ((up_down_ajust - 1) * body.s.y / up_down_ajust),
                body.s.x - (2 * (body.s.x / edges_ajust)),
                (1.1 * (body.s.y / up_down_ajust)));
  for (integer_t index = 0; index < level->map_size; index++) {
    if (collision_line_rect(level->map[index].line, rect_check)) {
      if (level->map[index].repel == REPEL_PLATFORM) {
        return true;
      }
    }
  }
  return false;
}
