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

#include "entity/aspect.h"

aspect_t *aspect_init() {
  aspect_t *aspect = calloc(1, sizeof(aspect_t));
  aspect->context = NULL;
  aspect->process_events = NULL;
  aspect->fixed_update = NULL;
  aspect->variable_update = NULL;
  aspect->render = NULL;
  aspect->exit = NULL;
  return aspect;
}

void aspect_exit(aspect_t *aspect) {
  if (aspect->context != NULL && aspect->exit != NULL) {
    aspect->exit(aspect->context);
  }

  free(aspect);
}
