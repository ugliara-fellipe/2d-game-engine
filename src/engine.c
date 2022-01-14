#include "engine.h"
#include "trace.h"

extern const char *game_name();
extern void game_init(engine_t *engine);
extern void game_update(engine_t *engine, float delta);
extern void game_render(engine_t *engine);
extern void game_exit(engine_t *engine);

static engine_t *engine =
    &(engine_t){.window = NULL, .render = NULL, .running = true};

static void engine_init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    trace_crash("SDL_Init Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  engine->window =
      SDL_CreateWindow(game_name(), 100, 100, 620, 387, SDL_WINDOW_SHOWN);
  if (engine->window == NULL) {
    trace_crash("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  engine->render = SDL_CreateRenderer(
      engine->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (engine->render == NULL) {
    trace_crash("SDL_CreateRendetexturerer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
}

static void engine_exit() {
  SDL_DestroyRenderer(engine->render);
  SDL_DestroyWindow(engine->window);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  engine_init();

  game_init(engine);

  while (engine->running) {
    game_update(engine, 1.0f);
    game_render(engine);
  }

  game_exit(engine);

  engine_exit();

  return EXIT_SUCCESS;
}