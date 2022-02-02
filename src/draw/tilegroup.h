/*
MIT License

Copyright (c) 2022 Fellipe Augusto Ugliara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
assets->texture[index] = NULL;
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

#ifndef TILEGROUP_H
#define TILEGROUP_H

#include "assets/assets.h"
#include "toolbelt/shape.h"
#include "toolbelt/vector2d.h"

typedef struct tilegroup_s {
  SDL_Texture *texture;
  rect_t rect;
  v2d_t scala;
  real_t angle_degrees;
  SDL_RendererFlip flip;
} tilegroup_t;

tilegroup_t *tilegroup_init(v2d_t size);
void tilegroup_exit(tilegroup_t *tilegroup);

void tilegroup_tile(tilegroup_t *tilegroup, integer_t texture_index,
                    rect_t src_rect, v2d_t dst_pos, v2d_t scala,
                    real_t angle_degrees, SDL_RendererFlip flip);

void tilegroup_draw(tilegroup_t *tilegroup);

#endif
