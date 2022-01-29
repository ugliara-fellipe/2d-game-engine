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

#ifndef SPRITE_H
#define SPRITE_H

#include "assets/assets.h"
#include "draw/tile.h"
#include "toolbelt/vector2d.h"

typedef struct sprite_s {
  tile_t **tile;
  sec_t *timing;
  integer_t tile_amount;
  v2d_t pos;
  v2d_t scala;
  real_t angle_degrees;
  SDL_RendererFlip flip;
  integer_t current;
  sec_t delta;
} sprite_t;

sprite_t *sprite_init(integer_t tile_amount);
void sprite_exit(sprite_t *sprite);

void sprite_tile(sprite_t *sprite, integer_t texture_index, v2d_t src_pos,
                 v2d_t src_size, integer_t sprite_index, sec_t timing);

void sprite_update(sprite_t *sprite, sec_t delta);

void sprite_draw(sprite_t *sprite);

#endif
