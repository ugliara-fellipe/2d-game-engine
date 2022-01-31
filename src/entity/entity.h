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

#ifndef ENTITY_H
#define ENTITY_H

#include "engine/engine.h"
#include "entity/aspect.h"
#include "toolbelt/maths.h"

struct entity_s {
  bool enable;
  bool persist;
  aspect_t *aspect;
  entity_t *parent;
  integer_t my_index;
  entity_t **nodes;
  integer_t nodes_amount;
};

entity_t *entity_init(integer_t nodes_amount);
void entity_exit(entity_t *entity);

void entity_process_events(entity_t *entity, SDL_Event *event);
void entity_fixed_update(entity_t *entity, sec_t delta);
void entity_variable_update(entity_t *entity, sec_t delta);
void entity_render(entity_t *entity, sec_t delta);

void entity_node(entity_t *entity, integer_t index, entity_t *node);

#endif
