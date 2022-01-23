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

#include "draw/text.h"
#include "assets/assets.h"
#include "engine/engine.h"

void text_draw(integer_t index, v2d_t dst_pos, v2d_t dst_size, SDL_Color color,
               const char *format, ...) {
  va_list args;
  va_start(args, format);
  char msg[100];
  vsnprintf(msg, 99, format, args);
  SDL_Surface *surface_message =
      TTF_RenderText_Solid(assets->font[index], msg, color);
  SDL_Texture *message =
      SDL_CreateTextureFromSurface(engine->render, surface_message);
  SDL_Rect rect = {dst_pos.x, dst_pos.y, dst_size.x, dst_size.y};
  SDL_RenderCopy(engine->render, message, NULL, &rect);
  SDL_FreeSurface(surface_message);
  SDL_DestroyTexture(message);
  va_end(args);
}
