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

#include "object/world/door.h"
#include "actor/trajectory.h"
#include "context.h"

static void fixed_update(entity_t *entity, sec_t delta) {
  door_t *door = entity->aspect->context;
  player_t *player = ctx_player->aspect->context;
  if (collision_rect_rect(door->body, player->body)) {
    if (player->control.s) {
      door->press = true;
    }
    if (!player->control.s && door->press) {
      world_set_level(ctx_world, door->level);
      player->body.ptl = door->move_to;
      door->press = false;
      trajectory_init(
          &(player->trajectory),
          v2d_add(door->move_to, v2d_mult_sclr(player->body.s, 0.5)));
    }
  } else {
    door->press = false;
  }
}

static void render(entity_t *entity, sec_t delta) {
  door_t *door = entity->aspect->context;
  rect_t body = door->body;

  body.ptl = camera_world_to_screen(body.ptl);

  body.ptl = camera_zooming(body.ptl);
  body.s = v2d_mult_sclr(body.s, camera_zoom());

  SDL_Texture *current = SDL_GetRenderTarget(engine->render);
  SDL_SetRenderTarget(engine->render, engine->layers[door->layer]);
  rect_t border = body;
  border.s.x = border.s.x / 8;
  rect_draw(border, RGB_RED, true);
  border.ptl.x = border.ptl.x + (7 * border.s.x);
  rect_draw(border, RGB_RED, true);
  border = body;
  border.s.y = border.s.y / 8;
  rect_draw(border, RGB_RED, true);
  SDL_SetRenderTarget(engine->render, current);
}

entity_t *door_init(rect_t body, entity_t *to_level, v2d_t to_pos,
                    integer_t layer) {
  entity_t *door = entity_init(0);
  door->aspect = aspect_init();

  door_t *context = calloc(1, sizeof(door_t));
  context->body = body;
  context->level = to_level;
  context->move_to = to_pos;
  context->layer = layer;
  door->aspect->context = context;

  door->aspect->fixed_update = fixed_update;
  door->aspect->render = render;

  return door;
}