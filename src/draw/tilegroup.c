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

#include "draw/tilegroup.h"
#include "engine/engine.h"

tilegroup_t *tilegroup_init(v2d_t size) {
  tilegroup_t *tilegroup = calloc(1, sizeof(tilegroup_t));

  // Init texture
  tilegroup->texture =
      SDL_CreateTexture(engine->render, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, size.x, size.y);

  SDL_SetRenderTarget(engine->render, tilegroup->texture);
  SDL_RenderClear(engine->render);
  SDL_SetRenderTarget(engine->render, NULL);

  tilegroup->pos = v2d_zero;
  tilegroup->scala = v2d_one;
  tilegroup->angle_degrees = 0;
  tilegroup->flip = SDL_FLIP_NONE;

  return tilegroup;
}

void tilegroup_exit(tilegroup_t *tilegroup) {
  SDL_DestroyTexture(tilegroup->texture);
  free(tilegroup);
}

void tilegroup_tile(tilegroup_t *tilegroup, integer_t texture_index,
                    v2d_t src_pos, v2d_t src_size, v2d_t dst_pos, v2d_t scala,
                    real_t angle_degrees, SDL_RendererFlip flip) {
  // Attach the texture
  SDL_SetRenderTarget(engine->render, tilegroup->texture);

  // Now render to the texture
  SDL_Rect src_rect = {src_pos.x, src_pos.y, src_size.x, src_size.y};
  SDL_Rect dst_rect = {dst_pos.x, dst_pos.y, src_size.x * scala.x,
                       src_size.y * scala.y};

  SDL_RenderCopyEx(engine->render, assets->texture[texture_index], &src_rect,
                   &dst_rect, angle_degrees, NULL, flip);

  // Detach the texture
  SDL_SetRenderTarget(engine->render, NULL);
}

void tilegroup_draw(tilegroup_t *tilegroup) {
  int width;
  int height;
  SDL_QueryTexture(tilegroup->texture, NULL, NULL, &width, &height);

  SDL_Rect dst_rect = {tilegroup->pos.x, tilegroup->pos.y,
                       width * tilegroup->scala.x, height * tilegroup->scala.y};
  SDL_RenderCopyEx(engine->render, tilegroup->texture, NULL, &dst_rect,
                   tilegroup->angle_degrees, NULL, tilegroup->flip);
}