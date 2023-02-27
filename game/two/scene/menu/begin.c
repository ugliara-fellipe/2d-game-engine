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

#include "scene/menu/begin.h"
#include "context.h"

static void process_events(entity_t *entity, SDL_Event *event) {
  begin_t *begin = entity->aspect->context;

  if (event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      if (begin->selected == 0) {
        begin->selected = 4;
      } else {
        begin->selected--;
      }
      break;
    case SDLK_DOWN:
      if (begin->selected == 4) {
        begin->selected = 0;
      } else {
        begin->selected++;
      }
      break;
    case SDLK_z:
      if (begin->selected == 0) {
        ctx_world->enable = true;
        ctx_player->enable = true;
        entity->enable = false;
      } else if (begin->selected == 3) {
        entity->enable = false;
        menu_t *menu = ctx_menu->aspect->context;
        menu->badges->enable = true;
      }
      break;
    }
  }
}

static void fixed_update(entity_t *entity, sec_t delta) {}

static void variable_update(entity_t *entity, sec_t delta) {}

static SDL_Color is_selected(begin_t *begin, integer_t index) {
  return index == begin->selected ? RGB_WHITE : (SDL_Color){130, 130, 130, 255};
}

static void render(entity_t *entity, sec_t delta) {
  begin_t *begin = entity->aspect->context;

  integer_t x = camera_size().x / 10;

  rect_draw(rect_init(x, 0, 300, camera_size().y), (SDL_Color){80, 80, 80, 155},
            true);
  rect_draw(rect_init(x, 0, 2, camera_size().y), (SDL_Color){80, 80, 80, 200},
            true);
  rect_draw(rect_init(x + 300 - 2, 0, 2, camera_size().y),
            (SDL_Color){80, 80, 80, 200}, true);

  integer_t pivot = (camera_size().y / 2) - 100;

  text_draw(0, rect_init(x + 30, pivot - 60 - 30, 100.0 * (9.0 / 10.0), 30),
            is_selected(begin, 0), "Continue");
  text_draw(0, rect_init(x + 30, pivot - 30 - 15, 100.0 * (10.0 / 10.0), 30),
            is_selected(begin, 1), "Load Game");
  text_draw(0, rect_init(x + 30, pivot, 100.0 * (9.0 / 10.0), 30),
            is_selected(begin, 2), "New Game");
  text_draw(0, rect_init(x + 30, pivot + 30 + 15, 100.0 * (7.0 / 10.0), 30),
            is_selected(begin, 3), "Badges");
  text_draw(0, rect_init(x + 30, pivot + 60 + 30, 100.0 * (8.0 / 10.0), 30),
            is_selected(begin, 4), "Options");

  text_draw(0,
            rect_init(x + 30, camera_size().y - 40, 100.0 * (6.0 / 10.0), 20),
            (SDL_Color){130, 130, 130, 255}, "v.0.1");

  text_draw(0,
            rect_init(camera_size().x - 120, camera_size().y - 60,
                      200.0 * (11.0 / 22.0), 20),
            (SDL_Color){150, 150, 150, 255}, "[Z] Select");
  text_draw(0,
            rect_init(camera_size().x - 220, camera_size().y - 40,
                      200.0 * (22.0 / 22.0), 20),
            (SDL_Color){150, 150, 150, 255}, "[UP, DOWN] Navigation");
}

static void finish(void *context) {}

entity_t *begin_init() {
  entity_t *begin = entity_init(0);
  begin->aspect = aspect_init();

  begin_t *context = calloc(1, sizeof(begin_t));
  context->selected = 0;

  begin->aspect->context = context;
  begin->aspect->process_events = process_events;
  begin->aspect->fixed_update = fixed_update;
  begin->aspect->variable_update = variable_update;
  begin->aspect->render = render;
  begin->aspect->finish = finish;

  return begin;
}