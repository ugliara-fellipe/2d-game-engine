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

#include "draw/sprite.h"

sprite_t *sprite_init(integer_t tile_amount) {
  sprite_t *sprite = calloc(1, sizeof(sprite_t));

  sprite->tile = calloc(tile_amount, sizeof(tile_t *));
  sprite->timing = calloc(tile_amount, sizeof(sec_t));

  sprite->tile_amount = tile_amount;
  sprite->pos = v2d_zero;
  sprite->scala = v2d_one;
  sprite->angle_degrees = 0;
  sprite->flip = SDL_FLIP_NONE;

  sprite->current = 0;
  sprite->delta = 0;

  return sprite;
}

void sprite_exit(sprite_t *sprite) {
  for (integer_t index = 0; index < sprite->tile_amount; index++) {
    tile_exit(sprite->tile[index]);
  }
  free(sprite->timing);
  free(sprite);
}

void sprite_tile(sprite_t *sprite, integer_t texture_index, v2d_t src_pos,
                 v2d_t src_size, integer_t sprite_index, sec_t timing) {
  sprite->tile[sprite_index] = tile_init(texture_index, src_pos, src_size);
  sprite->timing[sprite_index] = timing;
}

void sprite_update(sprite_t *sprite, sec_t delta) {
  sec_t total_delta = sprite->delta + delta;
  if (sprite->timing[sprite->current] < total_delta) {
    sec_t part_delta = total_delta - sprite->timing[sprite->current];
    sprite->delta = part_delta;
    sprite->current =
        sprite->current < sprite->tile_amount - 1 ? sprite->current + 1 : 0;
  } else {
    sprite->delta = total_delta;
  }
}

void sprite_draw(sprite_t *sprite) {
  sprite->tile[sprite->current]->pos = sprite->pos;
  sprite->tile[sprite->current]->scala = sprite->scala;
  sprite->tile[sprite->current]->angle_degrees = sprite->angle_degrees;
  sprite->tile[sprite->current]->flip = sprite->flip;

  tile_draw(sprite->tile[sprite->current]);
}
