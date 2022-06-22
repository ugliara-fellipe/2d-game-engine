# Project Overview

This project is a 2D Game Engine developed in C and SDL2. It covers the common features 
required to create games how: play sounds and musics, check collisions between entities, 
draw functions, game loop with FPS (frames per second) control, a system of entities to 
organize the game in a tree, and the math functions to work with vector and shapes.

A sample is delivery together to help the new adepts to start to use this engine in 
owner games. In the next session, there are the instructions to install dependencies 
and compiler to this project.

# How compile the project

The dependencies can be installed in the Debian based distros with the follow command. 
If you use another distro or OS (operating system), you need to install SDL2, some 
plugins, and a C compiler.

```bash
sudo apt install gcc libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-image-dev libsdl2-gfx-dev
```

After install dependencies, run the follow command to compiler the project sample. Run 
in root folder, the Makefile folder. 

```bash
make
```

# Run the Example

Execute the command above to run the sample after compiler it.

```bash
./build/game
```

# Modules Brief

## Assets

This module allows load resources used in game projects. Use the follow functions 
to load and indexing fonts, musics, sounds, and textures. The index is necessary 
to use the resource loaded by other functions.

```C
// Load font ttf
void assets_font(integer_t index, const char *file, integer_t ptsize);

// Load Music wav
void assets_music(integer_t index, const char *file);

// Load sound wav
void assets_sound(integer_t index, const char *file);

// Load Image bmp
void assets_texture(integer_t index, const char *bmp_file);
```

## Audio

The audio module allows play sounds and musics. A sound is an audio that play from 
begin to end, it is used to perform effect audios like when a player that damage 
or get an item. 

```C
// Play a sound calling this function with a sound resource index
void sound_play(integer_t index);
```

If in the game some music need to be played use the functions above, they allow play, 
pause, stop, resume, and check if music resources. Musics different of sound can 
continue performed.

```C
void music_play(integer_t index);
void music_pause();
void music_resume();
void music_stop();
bool music_playing();
bool music_paused();
```

## Collision

The basic game physics are the collisions between geometric shapes. This module has 
functions to check if points, lines, circles, and rectangles are colliding between then. 
In the sample, you can find examples of use (*game/player.c in fixed_update()*).

```C
bool collision_point_point(point_t p1, point_t p2);
bool collision_point_circle(point_t p, circle_t c);
bool collision_circle_circle(circle_t c1, circle_t c2);
bool collision_point_rect(point_t p, rect_t r);
bool collision_rect_rect(rect_t r1, rect_t r2);
bool collision_circle_rect(circle_t c, rect_t r);
bool collision_line_point(line_t l, point_t p);
bool collision_line_circle(line_t l, circle_t c);
bool collision_line_line(line_t l1, line_t l2);
bool collision_line_rect(line_t l, rect_t r);
```

## Draw

This module has the functions to draw: graphics, sprites, texts, tiles, and
tilegroups. Graphics are the geometric figures as point, circle, rectangle, 
and line. Sprites are the sequence of tile figures that change in time, it is 
used to define animated images. Texts are strings, sequence of symbols, used 
to draw images with words. Tiles are static images or a part of a static image. 
Tilegroups are compositions of static images grouped in a single image.

```C
// Graphics
void point_draw(point_t point, SDL_Color color);
void circle_draw(circle_t circle, SDL_Color color, bool filled);
void rect_draw(rect_t rect, SDL_Color color, bool filled);
void line_draw(line_t line, SDL_Color color);

// Sprite
sprite_t *sprite_init(integer_t tile_amount);
void sprite_exit(sprite_t *sprite);
void sprite_tile(sprite_t *sprite, integer_t texture_index, rect_t src_rect,
                 integer_t sprite_index, sec_t timing);
void sprite_update(sprite_t *sprite, sec_t delta);
void sprite_draw(sprite_t *sprite);

// Text
void text_draw(integer_t index, rect_t dst_rect, SDL_Color color,
               const char *format, ...);

// Tile
tile_t *tile_init(integer_t texture_index, rect_t src_rect);
void tile_exit(tile_t *tile);
void tile_draw(tile_t *tile);

// Tilegroup
tilegroup_t *tilegroup_init(v2d_t size);
void tilegroup_exit(tilegroup_t *tilegroup);
void tilegroup_tile(tilegroup_t *tilegroup, integer_t texture_index,
                    rect_t src_rect, v2d_t dst_pos, v2d_t scala,
                    real_t angle_degrees, SDL_RendererFlip flip);
void tilegroup_draw(tilegroup_t *tilegroup);
```

## Engine

Engine module do not have functions to be used direct. This module implements the 
game loop and control the updates and draw intervals during the game execution. 
The relevant element here is the engine object that allow the game access to the 
follow structure.

```C
#define LAYERS_SIZE 5

typedef struct engine_s {
  SDL_Window *window;
  SDL_Renderer *render;
  SDL_Texture *layers[LAYERS_SIZE];
  bool running;
  real_t update_rate;
  bool timing_resync;
  bool show_fps;
} engine_t;

extern engine_t *engine;
```

## Entity

The entity systems are used a lot in game development. It organizes the game in 
entities, each entity, have functions to define update and draw. An entity is 
a natural way to identify the parts of a game like the player, tan enemy, the map, 
a door, or anything in a game level. In the entity system, entities are organized in 
a tree. Each entity has their children, and an entity can be enabled or disabled. 
To perform an entity update, draw, add node, you need to use the entities 
functions that walk the entities tree and dispatch the actions if the visited entity 
is enable. 

```C
entity_t *entity_init(integer_t nodes_amount);
void entity_exit(entity_t *entity);
void entity_process_events(entity_t *entity, SDL_Event *event);
void entity_fixed_update(entity_t *entity, sec_t delta);
void entity_variable_update(entity_t *entity, sec_t delta);
void entity_render(entity_t *entity, sec_t delta);
void entity_node(entity_t *entity, integer_t index, entity_t *node);
```

## Toolbelt

This module is a collection of mathematics functions. There are functions
to instantiate shape objects like points, circles, rectangles, and lines. 
There are also functions to create and perform arithmetic in 2D vectors.

```C
// Maths
real_t math_max(real_t a, real_t b);
real_t math_min(real_t a, real_t b);
real_t math_abs(real_t n);
real_t math_clamp(real_t n, real_t min, real_t max);
real_t math_lerp(real_t n1, real_t n2, real_t t);
real_t math_lerpconst(real_t n1, real_t n2, real_t d);

// Shape
point_t point_init(real_t x, real_t y);
circle_t circle_init(real_t cx, real_t cy, real_t r);
rect_t rect_init(real_t ptlx, real_t ptly, real_t w, real_t h);
line_t line_init(real_t p1x, real_t p1y, real_t p2x, real_t p2y);

//Vector2d
extern v2d_t v2d_zero;
extern v2d_t v2d_one;
v2d_t v2d_init(const real_t x, const real_t y);
bool v2d_equal(v2d_t v1, v2d_t v2);
v2d_t v2d_add(v2d_t v1, v2d_t v2);
v2d_t v2d_sub(v2d_t v1, v2d_t v2);
v2d_t v2d_mult(v2d_t v1, v2d_t v2);
v2d_t v2d_neg(v2d_t v);
v2d_t v2d_mult_sclr(v2d_t v, real_t s);
real_t v2d_dot(v2d_t v1, v2d_t v2);
real_t v2d_cross(v2d_t v1, v2d_t v2);
v2d_t v2d_perp(v2d_t v);
v2d_t v2d_rperp(v2d_t v);
v2d_t v2d_project(v2d_t v1, v2d_t v2);
v2d_t v2d_forangle(real_t a);
real_t v2d_toangle(v2d_t v);
v2d_t v2d_rotate(v2d_t v1, v2d_t v2);
v2d_t v2d_unrotate(v2d_t v1, v2d_t v2);
real_t v2d_lengthsq(v2d_t v);
real_t v2d_length(v2d_t v);
v2d_t v2d_lerp(v2d_t v1, v2d_t v2, real_t t);
v2d_t v2d_normalize(v2d_t v);
v2d_t v2d_slerp(v2d_t v1, v2d_t v2, real_t t);
v2d_t v2d_slerpconst(v2d_t v1, v2d_t v2, real_t a);
```
