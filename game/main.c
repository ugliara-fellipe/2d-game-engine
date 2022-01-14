#include "engine.h"
#include "trace.h"

const char *game_name() { return "Game"; }

static SDL_Texture *texture = NULL;
static int exit_count = 20;

void game_init(engine_t *engine) {
  SDL_Surface *bmp = SDL_LoadBMP("assets/grumpy-cat.bmp");
  if (bmp == NULL) {
    trace_error("SDL_LoadBMP Error: %s\n", SDL_GetError());
    engine->running = false;
    return;
  }

  texture = SDL_CreateTextureFromSurface(engine->render, bmp);
  if (texture == NULL) {
    trace_error("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    SDL_FreeSurface(bmp);
    engine->running = false;
    return;
  }
  SDL_FreeSurface(bmp);
}

void game_update(engine_t *engine, float delta) {
  if (exit_count == 0) {
    engine->running = false;
  } else {
    exit_count--;
  }
}

void game_render(engine_t *engine) {
  SDL_RenderClear(engine->render);
  SDL_RenderCopy(engine->render, texture, NULL, NULL);
  SDL_RenderPresent(engine->render);
  SDL_Delay(100);
}

void game_exit(engine_t *engine) {
  if (texture == NULL) {
    SDL_DestroyTexture(texture);
  }
}