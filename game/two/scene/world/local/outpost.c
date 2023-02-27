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

#include "scene/world/local/outpost.h"
#include "object/world/door.h"
#include "object/world/ladder.h"
#include "scene/world/level.h"

static entity_t *level_main = NULL;
static entity_t *level_path = NULL;
static entity_t *level_tower = NULL;

static void outpost_main_map(entity_t *outpost) {
  char *map[] = {
      "CCCCCCCCCCCCCCCCCCCCCCCCCCC---------------CCCCCCCCCCCCCCCCCCCCCCC",
      "L-------------------------R--CCCCCCC------L---------------------R",
      "L-------------------------R--L-----R------L---------------------R",
      "L---PPFFF--FFFFFFFF-------R--L-----R------L---------------------R",
      "L-----R-L--R------L-------R--L-----R------FFFFFFFFFFFFF---------R",
      "L-----R-L--CCCCCCCC-------R--L-----R------------------LPPP------R",
      "L-----R-L-----------------R--L-----CCCCCCCCCCCCCCCCCCCC---------R",
      "L-----R-L-----------------R--L----------------------------------R",
      "L-----R-L-----------FFFFFFF--L------------------------------PPPPR",
      "L-----CCCPPP--------R--------L----------------------------------R",
      "L-------------------R--------L----------------------------------R",
      "L-------------------R--------L----------------------------------R",
      "FFFFFFFFFFFFF-------CCCCCCC--L----------FFFFFFFF----PPPPPP------R",
      "------------L-------------R--L----------R------L----------------R",
      "------------L-------------R--FFFFFF-----R------L----------------R",
      "------------L-------------R-------L-----R------L----------------R",
      "------------FFFFFFFFFFFFFFF-------FFFFFFF------FFFFFFFFFFFFFFFFFF"};

  level_matrix(level_main, map, 65, 17, 20);

  entity_node(level_main, 0,
              door_init(rect_init(350, 260, 60, 60), level_path,
                        v2d_init(100, 20 + 10), 2));

  entity_node(level_main, 1,
              door_init(rect_init(700, 260, 60, 60), level_path,
                        v2d_init(450, 20 + 10), 2));

  entity_node(level_main, 2,
              door_init(rect_init(410, 100, 60, 60), level_tower,
                        v2d_init(100, 420 + 10), 4));

  level_main->enable = false;
  entity_node(outpost, 0, level_main);
}

static void outpost_secret_path(entity_t *outpost) {
  char *map[] = {"CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC",
                 "L--------------------------------R",
                 "L--------------------------------R",
                 "L--------------------------------R",
                 "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"};

  level_matrix(level_path, map, 34, 5, 20);

  entity_node(level_path, 0,
              door_init(rect_init(100, 20, 60, 60), level_main,
                        v2d_init(350, 260 + 10), 4));

  entity_node(level_path, 1,
              door_init(rect_init(450, 20, 60, 60), level_main,
                        v2d_init(700, 260 + 10), 4));

  level_path->enable = false;
  entity_node(outpost, 1, level_path);
}

static void outpost_tower_map(entity_t *outpost) {
  char *map[] = {"CCCCCCCCCCCCCC",
                 "L------------R",
                 "L------------R",
                 "L------------R",
                 "L--------PPPPR",
                 "L------------R",
                 "L------------R",
                 "L------------R",
                 "L------------R",
                 "L------------R",
                 "L------------R",
                 "L------------R",
                 "FFFFFFFFFFFFFF"};

  level_matrix(level_tower, map, 14, 13, 40);

  entity_node(level_tower, 0,
              door_init(rect_init(100, 420, 60, 60), level_main,
                        v2d_init(410, 100 + 10), 2));

  entity_node(level_tower, 1,
              ladder_init(rect_init(200, 120, 50, 360), 0,
                        2));

  entity_node(level_tower, 2,
              ladder_init(rect_init(400, 160, 50, 320), 0,
                        2));

  level_tower->enable = false;
  entity_node(outpost, 2, level_tower);
}

entity_t *outpost_init() {
  entity_t *outpost = entity_init(3);

  level_main = level_init(39, 3);
  level_path = level_init(4, 2);
  level_tower = level_init(5, 3);

  outpost_main_map(outpost);
  outpost_secret_path(outpost);
  outpost_tower_map(outpost);

  return outpost;
}
