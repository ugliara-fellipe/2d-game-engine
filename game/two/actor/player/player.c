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

#include "context.h"

static const integer_t walking_value = 300;
static const integer_t running_value = 500;
static const integer_t clibing_value = 200;

static integer_t speed_value = walking_value;
static integer_t gravity_value = 400;

static integer_t jump_force_value = 50;

static void process_events(entity_t *entity, SDL_Event *event) {
  player_t *player = entity->aspect->context;

  if (menu_is_visible(ctx_menu)) {
    control_reset(&(player->control));
    return;
  }

  control_process_events(&(player->control), event);

  speed_value = player->control.x ? running_value : walking_value;

  if (player->control.z) {
    if (player->jump_release) {
      player->jump = true;
      player->jump_release = false;
      if (player->jumping) {
        player->jump_buffer = true;
      }
    }
  } else {
    player->jump = false;
    player->jump_release = true;
  }
}

static void fixed_update(entity_t *entity, sec_t delta) {
  player_t *player = entity->aspect->context;
  if (menu_is_visible(ctx_menu)) {
    control_reset(&(player->control));
    return;
  }
}

static void variable_update(entity_t *entity, sec_t delta) {
  player_t *player = entity->aspect->context;
  rect_t body = player->body;
  v2d_t direction = player->control.direction;
  v2d_t speed = v2d_init(speed_value * delta, 0);

  real_t gravity = gravity_value * delta;

  if (player->on_ladder &&
      ((player->control.up &&
        (player->jump_force > 0 && player->jump_force < 5) &&
        (player->jumping)) ||
       (player->control.down &&
        !level_is_on_floor(world_get_level(ctx_world), player->body) &&
        (player->jump_force > 0 && player->jump_force < 5)) ||
       (player->control.down &&
        level_is_on_platform(world_get_level(ctx_world), player->body))) &&
      !player->jump_ladder) {
    player->is_ladder = true;
    player->jumping = false;
  }

  if (!player->on_ladder) {
    if (player->is_ladder) {
      player->jump_ladder = true;
      player->jumping = false;
    }
    player->is_ladder = false;
  }

  if (!player->jump && player->jumping && player->jump_force > 2) {
    player->jump_force = 2;
  }

  if (!player->control.x &&
      (level_is_on_floor(world_get_level(ctx_world), player->body) ||
       level_is_on_platform(world_get_level(ctx_world), player->body))) {
    player->plat_down_release = true;
  }

  if (player->jump && !player->jumping && player->jump_delay == 0 &&
      (level_is_on_floor(world_get_level(ctx_world), player->body) ||
       level_is_on_platform(world_get_level(ctx_world), player->body))) {
    speed.y = speed_value * delta;
    player->jump_force = jump_force_value;
    player->jumping = true;
    player->jump_buffer = false;
  } else {
    if (player->jump_force > 0) {
      if (player->jump_force > jump_force_value * 0.7) {
        speed.y = gravity_value * delta;
      } else {
        speed.y =
            gravity_value * delta * (player->jump_force / jump_force_value);
      }
      player->jump_force--;
    } else {
      direction.y = 0;
    }
  }

  if (player->is_ladder) {
    gravity = 0;
    if (!player->jump_ladder) {
      if (player->control.up) {
        real_t move = clibing_value * delta;
        real_t ladder_top = player->ladder_body.ptl.y;
        real_t palyer_botton = player->body.ptl.y + player->body.s.y;
        if (palyer_botton - move >= ladder_top) {
          speed.y = move;
        } else {
          speed.y = palyer_botton - ladder_top;
        }
        direction.y = -1;
        player->jumping = false;
      }
      if (player->control.down) {
        real_t move = clibing_value * delta;
        real_t ladder_botton =
            player->ladder_body.ptl.y + player->ladder_body.s.y;
        real_t palyer_botton = player->body.ptl.y + player->body.s.y;
        if (palyer_botton + move <= ladder_botton) {
          speed.y = move;
        } else {
          speed.y = ladder_botton - palyer_botton;
          player->is_ladder = false;
        }
        direction.y = 1;
        player->jumping = false;
      }

      real_t move = clibing_value * delta;
      real_t ladder_top = player->ladder_body.ptl.y;
      real_t palyer_botton = player->body.ptl.y + player->body.s.y;
      if (palyer_botton - move < ladder_top) {
        if (player->jump && !player->jumping && player->jump_delay == 0) {
          speed.y = speed_value * delta;
          player->jump_force = jump_force_value;
          player->jumping = true;
          player->jump_buffer = false;
          player->jump_ladder = true;
          player->is_ladder = false;
        }
      }
    }
  }

  player->body.ptl = level_collision_update(world_get_level(ctx_world), body,
                                            direction, speed, gravity);

  if (player->jumping &&
      (level_is_on_floor(world_get_level(ctx_world), player->body) ||
       level_is_on_platform(world_get_level(ctx_world), player->body))) {
    player->jumping = false;
    player->jump_ladder = false;
    if (!player->jump_buffer) {
      player->jump = false;
    }
  }

  if (player->jump_ladder &&
      (level_is_on_floor(world_get_level(ctx_world), player->body) ||
       level_is_on_platform(world_get_level(ctx_world), player->body))) {
    player->jump_ladder = false;
  }

  if (level_is_on_celling(world_get_level(ctx_world), body) &&
      player->jump_force > 2) {
    player->jump_force = 2;
  }

  if (level_is_on_platform(world_get_level(ctx_world), player->body) &&
      player->control.down && player->control.x && player->plat_down_release) {
    player->body.ptl.y = player->body.ptl.y + (player->body.s.y / 3);
    player->plat_down_release = false;
  }

  camera_move(
      v2d_add(v2d_add(player->body.ptl, v2d_mult_sclr(player->body.s, 0.5)),
              player->camera_distance));

  // Update move array
  trajectory_update(&(player->trajectory),
                    point_init(player->body.ptl.x + (player->body.s.x / 2),
                               player->body.ptl.y + (player->body.s.y / 2)));
}

static void render(entity_t *entity, sec_t delta) {
  player_t *player = entity->aspect->context;
  rect_t body = player->body;

  v2d_t margin = v2d_init(2, 2);
  body.ptl = v2d_sub(
      v2d_sub(v2d_mult_sclr(camera_size(), 0.5), v2d_mult_sclr(body.s, 0.5)),
      player->camera_distance);
  body.ptl = v2d_add(body.ptl, margin);
  body.s = v2d_sub(body.s, v2d_add(v2d_one, margin));

  body.ptl = camera_zooming(body.ptl);
  body.s = v2d_mult_sclr(body.s, camera_zoom());

  trajectory_render(&(player->trajectory));
  SDL_Color color = RGB_WHITE;
  bool filled = false;
  if (player->on_ladder) {
    color = (SDL_Color){0, 0, 255, 205};
    filled = true;
  }
  rect_draw(body, color, filled);
}

static void finish(void *context) {}

entity_t *player_init() {
  entity_t *player = entity_init(0);
  player->aspect = aspect_init();

  player_t *context = calloc(1, sizeof(player_t));
  context->body = rect_init(40, 40, 50, 50);
  context->camera_distance = v2d_init(0, -70);
  control_init(&(context->control));
  trajectory_init(&(context->trajectory), point_init(65, 65));
  context->jump = false;
  context->jumping = false;
  context->jump_release = true;
  context->jump_buffer = false;
  context->plat_down_release = true;
  context->jump_force = 0;
  context->jump_delay = 0;
  context->on_ladder = false;
  context->is_ladder = false;
  context->jump_ladder = false;
  player->aspect->context = context;

  player->aspect->process_events = process_events;
  player->aspect->fixed_update = fixed_update;
  player->aspect->variable_update = variable_update;
  player->aspect->render = render;
  player->aspect->finish = finish;

  player->enable = false;

  return player;
}
