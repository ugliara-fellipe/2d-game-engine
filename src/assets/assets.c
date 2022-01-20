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

void assets_init() { assets_font(0, "assets/bgroveb.ttf", 24); }

void assets_exit() {}

void assets_font(integer_t index, const char *file, integer_t ptsize) {
  assets->font[index] = TTF_OpenFont(file, ptsize);
  if (assets->font[index] == NULL) {
    trace_crash("Font not found, TTF_OpenFont\n");
    engine->running = false;
  }
}
