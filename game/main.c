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

#include "game.h"
#include "level.h"
#include "player.h"

const char *game_name() { return "Game"; }
integer_t game_font_amount() { return 0; }
integer_t game_music_amount() { return 1; }
integer_t game_sound_amount() { return 1; }
integer_t game_texture_amount() { return 1; };

static tile_t *tile = NULL;
static sprite_t *sprite = NULL;
static tilegroup_t *group = NULL;
static bool zoom_in = true;

static entity_t *scene;

void game_init() {
  trace_debug("game_init\n");
  assets_music(0, "assets/music.wav");
  assets_sound(0, "assets/sound.wav");

  assets_texture(0, "assets/grumpy-cat.bmp");
  tile = tile_init(0, rect_init(100, 100, 60, 60));
  tile->rect.ptl = v2d_init(500, 250);

  sprite = sprite_init(3);
  sprite_tile(sprite, 0, rect_init(50, 50, 50, 50), 0, 0.4);
  sprite_tile(sprite, 0, rect_init(100, 100, 50, 50), 1, 0.4);
  sprite_tile(sprite, 0, rect_init(150, 150, 50, 50), 2, 0.7);
  sprite->rect.ptl = v2d_init(300, 250);

  group = tilegroup_init(v2d_init(100, 100));
  tilegroup_tile(group, 0, rect_init(25, 25, 50, 50), v2d_zero, v2d_one, 0,
                 SDL_FLIP_NONE);
  tilegroup_tile(group, 0, rect_init(125, 125, 75, 75), v2d_init(25, 25),
                 v2d_one, 0, SDL_FLIP_NONE);
  group->rect.ptl = v2d_init(400, 200);
  group->flip = SDL_FLIP_VERTICAL;

  music_play(0);

  scene = entity_init(2);
  entity_node(scene, 0, level_init());
  entity_node(scene, 1, player_init());
}

void game_process_events(SDL_Event *event) {
  trace_debug("game_process_events\n");
  if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_q) {
    engine->running = false;
    return;
  }
  entity_process_events(scene, event);
}

void game_fixed_update(sec_t delta) {
  trace_debug("game_fixed_update:    delta: %f s\n", delta);
  entity_fixed_update(scene, delta);

  if (tile->angle_degrees < 360) {
    tile->angle_degrees += 2;
    group->rect.ptl = v2d_add(group->rect.ptl, v2d_init(1, -1));
  } else {
    tile->angle_degrees = 0;
    group->rect.ptl = v2d_init(400, 200);
    zoom_in = !zoom_in;
    if (music_paused()) {
      music_resume();
    } else {
      music_pause();
    }
    sound_play(0);
  }
  if (zoom_in) {
    tile->scala = v2d_lerp(tile->scala, v2d_init(0.2, 0.2), 0.01);
  } else {
    tile->scala = v2d_lerp(tile->scala, v2d_init(4, 4), 0.01);
  }
}

void game_variable_update(sec_t delta) {
  trace_debug("game_variable_update: delta: %f s\n", delta);
  entity_variable_update(scene, delta);
  sprite_update(sprite, delta);
}

void game_render(sec_t delta) {
  trace_debug("game_render:          delta: %f s\n", delta);
  player_t *player = scene->nodes[1]->aspect->context;
  SDL_Rect dst_rect = {0, 0, 266, 200};
  SDL_RenderCopy(engine->render, assets->texture[0], NULL, &dst_rect);
  tilegroup_draw(group);
  tile_draw(tile);
  sprite_draw(sprite);

  if (collision_point_rect(point_init(150, 250), player->body)) {
    point_draw(point_init(150, 250), RGB_RED);
  } else {
    point_draw(point_init(150, 250), RGB_WHITE);
  }

  if (collision_circle_rect(circle_init(150, 300, 15), player->body)) {
    circle_draw(circle_init(150, 300, 15), RGB_RED, false);
  } else {
    circle_draw(circle_init(150, 300, 15), RGB_WHITE, true);
  }

  if (collision_rect_rect(rect_init(200, 220, 30, 30), player->body)) {
    rect_draw(rect_init(200, 220, 30, 30), RGB_RED, false);
  } else {
    rect_draw(rect_init(200, 220, 30, 30), RGB_WHITE, false);
  }

  if (collision_line_rect(line_init(300, 300, 400, 400), player->body)) {
    line_draw(line_init(300, 300, 400, 400), RGB_RED);
  } else {
    line_draw(line_init(300, 300, 400, 400), RGB_WHITE);
  }

  if (collision_line_circle(line_init(300, 300, 400, 400),
                            circle_init(350, 350, 30))) {
    circle_draw(circle_init(350, 350, 30), RGB_BLUE, false);
  }

  if (collision_line_line(line_init(300, 300, 400, 400),
                          line_init(300, 400, 400, 300))) {
    line_draw(line_init(300, 400, 400, 300), RGB_GREEN);
  }

  text_draw(0, rect_init(30, 410, 200, 20), RGB_WHITE, "Press < q > to exit");
  entity_render(scene, delta);
}

void game_exit() {
  music_stop();
  tile_exit(tile);
  sprite_exit(sprite);
  tilegroup_exit(group);
  entity_exit(scene);
  trace_debug("game_exit\n");
}
