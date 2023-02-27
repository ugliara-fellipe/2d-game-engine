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

#include "scene/menu/badges.h"
#include "context.h"

static void process_events(entity_t *entity, SDL_Event *event) {}

static void fixed_update(entity_t *entity, sec_t delta) {}

static void variable_update(entity_t *entity, sec_t delta) {}

static void render(entity_t *entity, sec_t delta) {
  text_draw(0, rect_init(200, 200, 100, 50), RGB_WHITE, "Badges");
}

static void finish(void *context) {}

entity_t *badges_init() {
  entity_t *badges = entity_init(0);
  badges->aspect = aspect_init();

  badges_t *context = calloc(1, sizeof(badges_t));

  badges->aspect->context = context;
  badges->aspect->process_events = process_events;
  badges->aspect->fixed_update = fixed_update;
  badges->aspect->variable_update = variable_update;
  badges->aspect->render = render;
  badges->aspect->finish = finish;

  badges->enable = false;

  return badges;
}
