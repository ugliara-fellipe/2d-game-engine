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

#include "object/world/ladder.h"
#include "context.h"

static void variable_update(entity_t *entity, sec_t delta) {
  ladder_t *ladder = entity->aspect->context;
  player_t *player = ctx_player->aspect->context;
  if (collision_rect_rect(ladder->body, player->body)) {
    player->on_ladder = true;
    ladder->has_player = true;
    player->ladder_body = ladder->body;
  } else {
    if (ladder->has_player) {
      player->on_ladder = false;
      ladder->has_player = false;
    }
  }
}

static void render(entity_t *entity, sec_t delta) {
  ladder_t *ladder = entity->aspect->context;
  rect_t body = ladder->body;

  body.ptl = camera_world_to_screen(body.ptl);

  body.ptl = camera_zooming(body.ptl);
  body.s = v2d_mult_sclr(body.s, camera_zoom());

  SDL_Texture *current = SDL_GetRenderTarget(engine->render);
  SDL_SetRenderTarget(engine->render, engine->layers[ladder->layer]);

  rect_draw(body, (SDL_Color){130, 130, 0, 200}, true);

  SDL_SetRenderTarget(engine->render, current);
}

// key - index of key necessary to use the ladder
entity_t *ladder_init(rect_t body, integer_t index_key, integer_t layer) {
  entity_t *ladder = entity_init(0);
  ladder->aspect = aspect_init();

  ladder_t *context = calloc(1, sizeof(ladder_t));
  context->body = body;
  context->index_key = index_key;
  context->layer = layer;
  context->has_player = false;
  ladder->aspect->context = context;

  ladder->aspect->variable_update = variable_update;
  ladder->aspect->render = render;

  return ladder;
}