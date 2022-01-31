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

#include "assets/assets.h"
#include "engine/engine.h"
#include "game.h"
#include "toolbelt/trace.h"

assets_t *assets = &(assets_t){};

void assets_init() {
  assets->font = calloc(game_font_amount() + 1, sizeof(TTF_Font *));
  assets->music = calloc(game_music_amount(), sizeof(Mix_Music *));
  assets->sound = calloc(game_sound_amount(), sizeof(Mix_Chunk *));
  assets->texture = calloc(game_texture_amount(), sizeof(SDL_Texture *));

  // Load font engine
  assets->font[game_font_amount()] = TTF_OpenFont("assets/pointfree.ttf", 128);
  if (assets->font[game_font_amount()] == NULL) {
    trace_crash("Font not found, TTF_OpenFont\n");
    engine->running = false;
    return;
  }

  // Init music array
  for (integer_t index = 0; index < game_music_amount(); index++) {
    assets->music[index] = NULL;
  }

  // Init sound array
  for (integer_t index = 0; index < game_sound_amount(); index++) {
    assets->sound[index] = NULL;
  }

  // Init texture array
  for (integer_t index = 0; index < game_texture_amount(); index++) {
    assets->texture[index] = NULL;
  }
}

void assets_exit() {
  for (integer_t index = 0; index < game_music_amount(); index++) {
    if (assets->music[index] == NULL) {
      Mix_FreeMusic(assets->music[index]);
      assets->music[index] = NULL;
    }
  }

  for (integer_t index = 0; index < game_sound_amount(); index++) {
    if (assets->sound[index] == NULL) {
      Mix_FreeChunk(assets->sound[index]);
      assets->sound[index] = NULL;
    }
  }

  for (integer_t index = 0; index < game_texture_amount(); index++) {
    if (assets->texture[index] == NULL) {
      SDL_DestroyTexture(assets->texture[index]);
      assets->texture[index] = NULL;
    }
  }

  free(assets->font);
  free(assets->music);
  free(assets->sound);
  free(assets->texture);
}

void assets_font(integer_t index, const char *file, integer_t ptsize) {
  if (index < 0 || index >= game_font_amount()) {
    trace_crash("Font invalid index\n");
    engine->running = false;
    return;
  }
  assets->font[index] = TTF_OpenFont(file, ptsize);
  if (assets->font[index] == NULL) {
    trace_crash("Font not found, TTF_OpenFont\n");
    engine->running = false;
    return;
  }
}

void assets_music(integer_t index, const char *file) {
  if (index < 0 || index >= game_music_amount()) {
    trace_crash("Music invalid index\n");
    engine->running = false;
    return;
  }

  assets->music[index] = Mix_LoadMUS(file);
  if (assets->music[index] == NULL) {
    trace_crash("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    engine->running = false;
  }
}

void assets_sound(integer_t index, const char *file) {
  if (index < 0 || index >= game_sound_amount()) {
    trace_crash("Sound invalid index\n");
    engine->running = false;
    return;
  }

  assets->sound[index] = Mix_LoadWAV(file);
  if (assets->sound[index] == NULL) {
    trace_crash("Failed to load sound effect! SDL_mixer Error: %s\n",
                Mix_GetError());
    engine->running = false;
  }
}

void assets_texture(integer_t index, const char *bmp_file) {
  if (index < 0 || index >= game_texture_amount()) {
    trace_crash("Texture invalid index\n");
    engine->running = false;
    return;
  }

  SDL_Surface *bmp = SDL_LoadBMP(bmp_file);
  if (bmp == NULL) {
    trace_error("SDL_LoadBMP Error: %s\n", SDL_GetError());
    engine->running = false;
    return;
  }

  if (assets->texture[index] != NULL) {
    SDL_DestroyTexture(assets->texture[index]);
    assets->texture[index] = NULL;
  }
  assets->texture[index] = SDL_CreateTextureFromSurface(engine->render, bmp);
  if (assets->texture[index] == NULL) {
    trace_error("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    SDL_FreeSurface(bmp);
    engine->running = false;
    return;
  }
  SDL_FreeSurface(bmp);
}
