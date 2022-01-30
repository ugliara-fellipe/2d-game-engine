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

#include "entity/entity.h"
#include "toolbelt/trace.h"

entity_t *entity_init(integer_t nodes_amount) {
  entity_t *entity = calloc(1, sizeof(entity_t));
  entity->enable = true;
  entity->persist = false;
  entity->aspect = NULL;
  entity->parent = NULL;
  entity->nodes =
      nodes_amount > 0 ? calloc(nodes_amount, sizeof(entity_t *)) : NULL;
  entity->nodes_amount = nodes_amount;
  return entity;
}

void entity_exit(entity_t *entity) {
  if (entity->persist) {
    return;
  }

  if (entity->aspect != NULL) {
    aspect_exit(entity->aspect);
  }

  if (entity->nodes != NULL) {
    for (integer_t index = 0; index < entity->nodes_amount; index++) {
      entity_exit(entity->nodes[index]);
    }
    free(entity->nodes);
  }

  free(entity);
}

void entity_process_events(entity_t *entity, SDL_Event *event) {
  if (!entity->enable) {
    return;
  }
  if (entity->aspect->process_events != NULL) {
    entity->aspect->process_events(entity, event);
  }
  for (integer_t index = 0; index < entity->nodes_amount; index++) {
    entity_process_events(entity->nodes[index], event);
  }
}

void entity_fixed_update(entity_t *entity, sec_t delta) {
  if (!entity->enable) {
    return;
  }
  if (entity->aspect->fixed_update != NULL) {
    entity->aspect->fixed_update(entity, delta);
  }
  for (integer_t index = 0; index < entity->nodes_amount; index++) {
    entity_fixed_update(entity->nodes[index], delta);
  }
}

void entity_variable_update(entity_t *entity, sec_t delta) {
  if (!entity->enable) {
    return;
  }
  if (entity->aspect->variable_update != NULL) {
    entity->aspect->variable_update(entity, delta);
  }
  for (integer_t index = 0; index < entity->nodes_amount; index++) {
    entity_variable_update(entity->nodes[index], delta);
  }
}

void entity_render(entity_t *entity, sec_t delta) {
  if (!entity->enable) {
    return;
  }
  if (entity->aspect->render != NULL) {
    entity->aspect->render(entity, delta);
  }
  for (integer_t index = 0; index < entity->nodes_amount; index++) {
    entity_render(entity->nodes[index], delta);
  }
}

void entity_node(entity_t *entity, integer_t index, entity_t *node) {
  if (index < 0 || index >= entity->nodes_amount) {
    trace_crash("Entity node invalid index\n");
    engine->running = false;
    return;
  }
  entity->nodes[index] = node;
  node->parent = entity;
}
