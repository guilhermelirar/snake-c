// game.h 
#ifndef GAME_H
#define GAME_H
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include <SDL2/SDL.h>

struct SnakePart {
  int x, y;
  struct SnakePart* previous;
};

struct Snake {
  int length;
  struct SnakePart* head;
  struct SnakePart* tail;
};

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  struct Snake *snake;
} Game;

Game* createGame();

void destroyGame(Game* game);

#endif // GAME_H
