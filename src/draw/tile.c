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

#include "draw/tile.h"
#include "engine/engine.h"
#include "toolbelt/trace.h"

tile_t *tile_init(integer_t texture_index, rect_t src_rect) {
  tile_t *tile = calloc(1, sizeof(tile_t));

  // Init texture
  tile->texture =
      SDL_CreateTexture(engine->render, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, src_rect.s.x, src_rect.s.y);

  // Attach the texture
  SDL_SetRenderTarget(engine->render, tile->texture);

  // Now render to the texture
  SDL_RenderClear(engine->render);
  SDL_Rect sdl_src_rect = {src_rect.ptl.x, src_rect.ptl.y, src_rect.s.x,
                           src_rect.s.y};
  SDL_Rect dst_rect = {0, 0, src_rect.s.x, src_rect.s.y};
  SDL_RenderCopy(engine->render, assets->texture[texture_index], &sdl_src_rect,
                 &dst_rect);

  // Detach the texture
  SDL_SetRenderTarget(engine->render, NULL);

  tile->rect = rect_init(0, 0, src_rect.s.x, src_rect.s.y);
  tile->scala = v2d_one;
  tile->angle_degrees = 0;
  tile->flip = SDL_FLIP_NONE;

  return tile;
}

void tile_exit(tile_t *tile) {
  SDL_DestroyTexture(tile->texture);
  free(tile);
}

void tile_draw(tile_t *tile) {
  SDL_Rect dst_rect = {tile->rect.ptl.x, tile->rect.ptl.y,
                       tile->rect.s.x * tile->scala.x,
                       tile->rect.s.y * tile->scala.y};
  SDL_RenderCopyEx(engine->render, tile->texture, NULL, &dst_rect,
                   tile->angle_degrees, NULL, tile->flip);
}
