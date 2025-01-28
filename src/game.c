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

  // Setting members
  pgame->window = window;
  pgame->renderer = renderer;
  pgame->snake = createStartSnake();
  initMap(pgame);

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

void initMap(Game *game) {
  // Initializing tilemap with void
  for (int y = 0; y < SCREEN_HEIGHT / TILE_SIZE; y++) {
    for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; x++) {
      game->map[y][x] = VOID;
    }
  }

  // Updating with the initial snake positions
  struct SnakePart *part = game->snake->head;
  while (part != NULL) {
    struct SnakePart *next = part->previous;
    game->map[part->y / TILE_SIZE][part->x / TILE_SIZE] = SNAKE;
    part = next;
  }
}


void render(Game *game) {
  SDL_Renderer *renderer = game->renderer;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_Rect whiteRect = {SCREEN_WIDTH - 150, SCREEN_HEIGHT - 100, 100,
                        50};

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &whiteRect);
  SDL_RenderPresent(renderer);
}
