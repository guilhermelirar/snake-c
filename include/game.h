// game.h 
#ifndef GAME_H
#define GAME_H
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 50
#define MAP_WIDTH SCREEN_WIDTH / TILE_SIZE
#define MAP_HEIGHT SCREEN_HEIGHT / TILE_SIZE

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
  RESET_REQUESTED,
  QUIT_REQUESTED
} GameStatus;

typedef TileStatus GameMap[MAP_HEIGHT][MAP_WIDTH];

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  Snake *snake;
  GameMap map;
  GameStatus status;
} Game;

/* Returns the Game pointer (singleton) */
Game* getGame();

/* Initialize game */
void startGame();

/* Render contents in window */
void drawGame();

/* Sets all positions of the map with VOID */
void initMap();

/* Frees resources */
void destroyGame();

/* Spawns one fruit on a previously VOID position 
 * of the map */
void spawnFruit();

/* Updates the Game state */
void update();

/* Runs the main loop */
void run();

#endif // GAME_H
