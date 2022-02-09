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

#include "player.h"
#include "level.h"

static int speed = 3;

static void process_events(entity_t *entity, SDL_Event *event) {
  player_t *player = entity->aspect->context;
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      player->direction = v2d_init(0, -speed);
      break;
    case SDLK_LEFT:
      player->direction = v2d_init(-speed, 0);
      break;
    case SDLK_RIGHT:
      player->direction = v2d_init(speed, 0);
      break;
    }
  } else if (event->type == SDL_KEYUP) {
    player->direction = v2d_init(0, 0);
  }
}

static void fixed_update(entity_t *entity, sec_t delta) {
  player_t *player = entity->aspect->context;
  v2d_t temp = v2d_add(player->body.pos_top_left, player->direction);

  level_t *level = entity->parent->nodes[0]->aspect->context;
  if ((!collision_line_rect(level->map[1], player->body) &&
       !collision_line_rect(level->map[3], player->body)) &&
      player->direction.y == 0) {
    temp.y = temp.y + speed;
  }
  if (collision_line_rect(level->map[5], player->body) &&
      player->direction.y == -speed) {
    temp.y = temp.y + speed;
  }
  if (collision_line_rect(level->map[0], player->body) &&
      player->direction.x == -speed) {
    temp.x = temp.x + speed;
  }
  if ((collision_line_rect(level->map[2], player->body) ||
       collision_line_rect(level->map[4], player->body)) &&
      player->direction.x == speed) {
    temp.x = temp.x - speed;
  }

  player->body.pos_top_left = temp;
}

static void variable_update(entity_t *entity, sec_t delta) {}

static void render(entity_t *entity, sec_t delta) {
  player_t *player = entity->aspect->context;
  rect_t body = player->body;
  body.size.x -= 1;
  body.size.y -= 1;
  rect_draw(body, RGB_WHITE);
}

static void finish(void *context) {}

entity_t *player_init() {
  entity_t *player = entity_init(0);
  player->aspect = aspect_init();

  player_t *context = calloc(1, sizeof(player_t));
  context->body = rect_init(100, 100, 50, 50);
  context->direction = v2d_zero;
  player->aspect->context = context;

  player->aspect->process_events = process_events;
  player->aspect->fixed_update = fixed_update;
  player->aspect->variable_update = variable_update;
  player->aspect->render = render;
  player->aspect->finish = finish;

  return player;
}
