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

#include "scene/menu/menu.h"
#include "scene/menu/badges.h"
#include "scene/menu/begin.h"
#include "scene/menu/charsheet.h"
#include "scene/menu/station.h"

static void process_events(entity_t *entity, SDL_Event *event) {
  menu_t *menu = entity->aspect->context;
  if (event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
    case SDLK_u:
      if (!menu->charsheet->enable) {
        menu->station->enable = !menu->station->enable;
      }
      break;
    case SDLK_i:
      if (!menu->station->enable) {
        menu->charsheet->enable = !menu->charsheet->enable;
      }
      break;
    }
  }
}

entity_t *menu_init() {
  entity_t *menu = entity_init(4);
  menu->aspect = aspect_init();

  menu_t *context = calloc(1, sizeof(menu_t));
  context->charsheet = charsheet_init();
  entity_node(menu, 0, context->charsheet);
  context->station = station_init();
  entity_node(menu, 1, context->station);

  context->begin = begin_init();
  entity_node(menu, 2, context->begin);
  context->badges = badges_init();
  entity_node(menu, 3, context->badges);

  menu->aspect->context = context;
  menu->aspect->process_events = process_events;

  return menu;
}

bool menu_is_visible(entity_t *menu) {
  menu_t *context = menu->aspect->context;
  return (context->charsheet->enable || context->station->enable);
}