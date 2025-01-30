#include "../include/snake.h"
#include "../include/game.h"

#include <stdio.h>
#include <stdlib.h>
// Free resources
void destroySnake(Snake* snake) {
  struct SnakePart *part = snake->head;
  while (part != NULL) {
    struct SnakePart *next = part->previous;
    free(part);
    part = next;
  }
  free(snake);
}

struct SnakePart* newPart(int x, int y, struct SnakePart* previous) {
  struct SnakePart* np = malloc(sizeof(struct SnakePart));
  if (!np) {
    return NULL;
  }
  np->x = x; np->y = y;
  np->previous = previous;
  return np;
}


void growSnake(Snake* snake) {
  Direction dir = snake->dir;
  SnakePart* part = (SnakePart*)malloc(sizeof(SnakePart));

  // Index of the new head
  part->x = snake->head->x + (dir == RIGHT) - (dir == LEFT);
  part->y = snake->head->y + (dir == DOWN) - (dir == UP);

  getGame()->map[part->y][part->x] = SNAKE;

  // Linking into the snake
  part->previous = snake->head;
  part->next = NULL;
  snake->head = part;
  part->previous->next = part;

  snake->length++;
}

// Creates snake with 3 parts
Snake* initSnake() {
  Snake* psnake = (Snake*)malloc(sizeof(Snake));
  if (!psnake) {
    return NULL;
  }

  int widthInTiles = (SCREEN_WIDTH / TILE_SIZE);
  int heightInTiles = (SCREEN_HEIGHT/ TILE_SIZE);

  // Init first part of the snake
  SnakePart* tail0 = (SnakePart*)malloc(sizeof(SnakePart));
  tail0->x = widthInTiles / 2;
  tail0->y = heightInTiles - 1;
  tail0->next = NULL; tail0->previous = NULL;
  psnake->head = tail0;
  psnake->tail = tail0;
  

  getGame()->map[tail0->y][tail0->x] = SNAKE;

  psnake->dir = UP;
  psnake->length = 1;

  growSnake(psnake);
  growSnake(psnake);

  return psnake;
};
