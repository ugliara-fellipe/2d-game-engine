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
#include "scene/world/world.h"
#include "scene/world/local/outpost.h"

entity_t *world_init() {
  entity_t *world = entity_init(1);
  world->aspect = aspect_init();

  world_t *context = calloc(1, sizeof(world_t));
  entity_node(world, 0, outpost_init());
  context->level = world->nodes[0]->nodes[0];
  context->level->enable = true;

  world->aspect->context = context;

  camera_set(v2d_init(800, 450), v2d_init(800, 450));

  world->enable = false;
  return world;
}

level_t *world_get_level(entity_t *world) {
  world_t *context = world->aspect->context;
  return context->level->aspect->context;
}

void world_set_level(entity_t *world, entity_t *level) {
  world_t *context = world->aspect->context;

  context->level->enable = false;
  context->level = level;
  context->level->enable = true;
}
