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

#ifndef GAME_H
#define GAME_H

#include "assets/assets.h"
#include "audio/music.h"
#include "audio/sound.h"
#include "draw/color.h"
#include "draw/graphics.h"
#include "draw/particles.h"
#include "draw/sprite.h"
#include "draw/text.h"
#include "draw/tile.h"
#include "draw/tilegroup.h"
#include "engine/engine.h"
#include "toolbelt/maths.h"
#include "toolbelt/trace.h"
#include "toolbelt/vector2d.h"

extern const char *game_name();
extern void game_init();
extern void game_process_events(SDL_Event *event);
extern void game_fixed_update(real_t delta);
extern void game_variable_update(real_t delta);
extern void game_render(real_t delta);
extern void game_exit();

#endif
