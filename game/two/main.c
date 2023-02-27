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

#include "context.h"
#include "game.h"

const char *game_name() { return "Stellar Exile"; }
integer_t game_font_amount() { return 0; }
integer_t game_music_amount() { return 0; }
integer_t game_sound_amount() { return 0; }
integer_t game_texture_amount() { return 0; };

void game_init() {
  ctx_scene = entity_init(3);

  ctx_menu = menu_init();
  ctx_world = world_init();
  ctx_player = player_init();

  entity_node(ctx_scene, 0, ctx_menu);
  entity_node(ctx_scene, 1, ctx_world);
  entity_node(ctx_scene, 2, ctx_player);
}

void game_process_events(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_q) {
    engine->running = false;
    return;
  }
  if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_m) {
    camera_set_zoom(camera_zoom() + 0.1);
  }
  if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_n) {
    camera_set_zoom(camera_zoom() - 0.1);
  }
  entity_process_events(ctx_scene, event);
}

void game_fixed_update(sec_t delta) { entity_fixed_update(ctx_scene, delta); }

void game_variable_update(sec_t delta) {
  entity_variable_update(ctx_scene, delta);
}

void game_render(sec_t delta) {
  text_draw(0, rect_init(600 - 20, 20, 200, 20), RGB_WHITE,
            "Press < q > to exit");
  entity_render(ctx_scene, delta);
}

void game_exit() { entity_exit(ctx_scene); }
