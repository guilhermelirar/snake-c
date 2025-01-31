#include "../include/snake.h"
#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>

// Free resources
void destroySnake(Snake* snake) {
  SnakePart* current = snake->head;
  while (current != NULL) {
    SnakePart* next = current->next;
    free(current);
    current = next;
  }

  free(snake);
}

void growSnake(Snake* snake) {
  if (snake == NULL) return;
  Direction dir = snake->dir;
  SnakePart* part = (SnakePart*)malloc(sizeof(SnakePart));

  // Index of the new head
  part->x = snake->head->x + (dir == RIGHT) - (dir == LEFT);
  part->y = snake->head->y + (dir == DOWN) - (dir == UP);

  getGame()->map[part->y][part->x] = SNAKE;

  // Linking into the snake
  part->previous = NULL;
  part->next = snake->head;
  snake->head->previous = part;
  snake->head = part;

  snake->length++;
}

void moveSnake(Snake *snake) {
  SnakePart *oldTail = snake->tail;
 
  // Unlinks the tail
  snake->tail = oldTail->previous; // New tail
  snake->tail->next = NULL; // Tail doesn't have a next
  int x = oldTail->x, y = oldTail->y; 

  free(oldTail);

  getGame()->map[y][x] = VOID;
  growSnake(snake);
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
