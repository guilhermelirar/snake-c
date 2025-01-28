// game.h 
#ifndef GAME_H
#define GAME_H
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 50 

#include <SDL2/SDL.h>
#include "snake.h"

typedef enum {
  SNAKE,
  VOID,
  FRUIT
} TileStatus;

typedef TileStatus GameMap[SCREEN_HEIGHT / TILE_SIZE][SCREEN_WIDTH / TILE_SIZE];

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  Snake *snake;
  GameMap map;
} Game;

Game* createGame();

// Update contents in window
void render(Game* game);
void initMap(Game* game);
void destroyGame(Game* game);

#endif // GAME_H
