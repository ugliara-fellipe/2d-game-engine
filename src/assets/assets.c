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

#include "assets/assets.h"
#include "engine/engine.h"
#include "toolbelt/trace.h"

assets_t *assets = &(assets_t){};

void assets_init() {
  assets_font(0, "assets/pointfree.ttf", 128);
  for (integer_t index = 0; index < ASSETS_TEXTURE_LIMIT; index++) {
    assets->texture[index] = NULL;
  }
}

void assets_exit() {
  for (integer_t index = 0; index < ASSETS_TEXTURE_LIMIT; index++) {
    if (assets->texture[index] == NULL) {
      SDL_DestroyTexture(assets->texture[index]);
    }
  }
}

void assets_font(integer_t index, const char *file, integer_t ptsize) {
  if (index < 0 || index >= ASSETS_FONT_LIMIT) {
    trace_crash("Font invalid index\n");
    engine->running = false;
    return;
  }
  assets->font[index] = TTF_OpenFont(file, ptsize);
  if (assets->font[index] == NULL) {
    trace_crash("Font not found, TTF_OpenFont\n");
    engine->running = false;
    return;
  }
}

void assets_texture(integer_t index, const char *bmp_file) {
  if (index < 0 || index >= ASSETS_TEXTURE_LIMIT) {
    trace_crash("Texture invalid index\n");
    engine->running = false;
    return;
  }

  SDL_Surface *bmp = SDL_LoadBMP(bmp_file);
  if (bmp == NULL) {
    trace_error("SDL_LoadBMP Error: %s\n", SDL_GetError());
    engine->running = false;
    return;
  }

  if (assets->texture[index] != NULL) {
    SDL_DestroyTexture(assets->texture[index]);
    assets->texture[index] = NULL;
  }
  assets->texture[index] = SDL_CreateTextureFromSurface(engine->render, bmp);
  if (assets->texture[index] == NULL) {
    trace_error("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    SDL_FreeSurface(bmp);
    engine->running = false;
    return;
  }
  SDL_FreeSurface(bmp);
}
