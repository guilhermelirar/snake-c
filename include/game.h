// game.h 
#ifndef GAME_H
#define GAME_H
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 50 

#include <SDL2/SDL.h>
typedef struct Snake Snake;

typedef enum {
  SNAKE,
  VOID,
  FRUIT
} TileStatus;

typedef enum {
  RUNNING,
  PAUSED,
  QUIT_REQUESTED
} GameStatus;

typedef TileStatus GameMap[SCREEN_HEIGHT / TILE_SIZE][SCREEN_WIDTH / TILE_SIZE];

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  Snake *snake;
  GameMap map;
  GameStatus status;
} Game;

Game* getGame();

// Update contents in window
void drawGame();
void initMap();
void destroyGame();

/* Updates the state of the game */
void update();
void run();

#endif // GAME_H
