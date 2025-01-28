#include "../include/snake.h"
#include "../include/game.h"

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

// Creates snake with 3 parts
Snake* createStartSnake() {
  Snake* psnake = (Snake*)malloc(sizeof(Snake));
  if (!psnake) {
    return NULL;
  }

  psnake->dir = TOP;

  struct SnakePart* p1 = newPart(400, 500, NULL);
  struct SnakePart* p2 = newPart(400, 500 - TILE_SIZE, p1);
  struct SnakePart* p3 = newPart(400, 500 - TILE_SIZE * 2, p2);
  psnake->head = p3;
  psnake->tail = p1;

  return psnake;
};


