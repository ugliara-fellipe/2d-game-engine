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

tile_t *tile_init(integer_t texture_index, v2d_t src_pos, v2d_t src_size) {
  tile_t *tile = calloc(1, sizeof(tile_t));

  // Init tile struct
  tile->texture =
      SDL_CreateTexture(engine->render, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, src_size.x, src_size.y);

  // Attach the texture
  SDL_SetRenderTarget(engine->render, tile->texture);

  // Now render to the texture
  SDL_RenderClear(engine->render);
  SDL_Rect src_rect = {src_pos.x, src_pos.y, src_size.x, src_size.y};
  SDL_Rect dst_rect = {0, 0, src_size.x, src_size.y};
  SDL_RenderCopy(engine->render, assets->texture[texture_index], &src_rect,
                 &dst_rect);

  // Detach the texture
  SDL_SetRenderTarget(engine->render, NULL);

  return tile;
}

void tile_exit(tile_t *tile) {
  SDL_DestroyTexture(tile->texture);
  free(tile);
}

void draw_tile(tile_t *tile, v2d_t dst_pos, real_t angle_degrees,
               SDL_RendererFlip flip) {
  int width;
  int height;
  SDL_QueryTexture(tile->texture, NULL, NULL, &width, &height);

  SDL_Rect dst_rect = {dst_pos.x, dst_pos.y, width, height};
  SDL_RenderCopyEx(engine->render, tile->texture, NULL, &dst_rect,
                   angle_degrees, NULL, flip);
}
