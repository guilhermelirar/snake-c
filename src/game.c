#include "../include/game.h"
#include "../include/snake.h"
#include <stdlib.h>

Game* createGame() {
  // Initializing SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error when initializing SDL: %s\n", SDL_GetError());
    return NULL;
  }

  // Window
  SDL_Window *window = SDL_CreateWindow(
      "SNAKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Error when creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return NULL;
  }

  // Creating renderer 
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  if (!renderer) {
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return NULL;
  }

  Game *pgame = (Game*)malloc(sizeof(Game));

  if (!pgame) {
    printf("Error when creating window: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }

  pgame->window = window;
  pgame->renderer = renderer;
  pgame->snake = createStartSnake();
 
  return pgame;
}

void destroyGame(Game* game) {  
  if (game->renderer) {
    SDL_DestroyRenderer(game->renderer);
  }

  if (game->window) {
    SDL_DestroyWindow(game->window); 
  }

  if (game->snake) {
    destroySnake(game->snake); 
  }

  free(game);
  SDL_Quit();
}
