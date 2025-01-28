// game.h 
#ifndef GAME_H
#define GAME_H
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 50 

#include <SDL2/SDL.h>
#include "snake.h"

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  Snake *snake;
} Game;

Game* createGame();

void destroyGame(Game* game);

#endif // GAME_H
