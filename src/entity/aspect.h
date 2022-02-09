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

#ifndef ASPECT_H
#define ASPECT_H

#include "engine/engine.h"
#include "toolbelt/maths.h"

typedef struct entity_s entity_t;

typedef struct aspect_s {
  void *context;
  void (*process_events)(entity_t *entity, SDL_Event *event);
  void (*fixed_update)(entity_t *entity, sec_t delta);
  void (*variable_update)(entity_t *entity, sec_t delta);
  void (*render)(entity_t *entity, sec_t delta);
  void (*finish)(void *context);
} aspect_t;

aspect_t *aspect_init();
void aspect_exit(aspect_t *aspect);

#endif
