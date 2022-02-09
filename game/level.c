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

#include "level.h"
#include "player.h"

static void process_events(entity_t *entity, SDL_Event *event) {}

static void fixed_update(entity_t *entity, sec_t delta) {
  level_t *level = entity->aspect->context;
}

static void variable_update(entity_t *entity, sec_t delta) {}

static void render(entity_t *entity, sec_t delta) {
  level_t *level = entity->aspect->context;
  for (int index = 0; index < 6; index++) {
    line_draw(level->map[index], RGB_WHITE);
  }
}

static void finish(void *context) {}

entity_t *level_init() {
  entity_t *level = entity_init(0);
  level->aspect = aspect_init();

  int w, h;
  SDL_GetWindowSize(engine->window, &w, &h);

  level_t *context = calloc(1, sizeof(level_t));
  context->map[0] = line_init(10, 10, 10, h - 10);
  context->map[1] = line_init(10, h - 10, w - 10 - 100, h - 10);
  context->map[2] = line_init(w - 10 - 100, h - 10, w - 10 - 100, h - 10 - 100);
  context->map[3] = line_init(w - 10 - 100, h - 10 - 100, w - 10, h - 10 - 100);
  context->map[4] = line_init(w - 10, h - 10 - 100, w - 10, 10);
  context->map[5] = line_init(w - 10, 10, 10, 10);
  level->aspect->context = context;

  level->aspect->process_events = process_events;
  level->aspect->fixed_update = fixed_update;
  level->aspect->variable_update = variable_update;
  level->aspect->render = render;
  level->aspect->finish = finish;

  return level;
}