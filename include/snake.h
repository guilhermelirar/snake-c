#ifndef SNAKE_H
#define SNAKE_H

typedef enum {
  UP, DOWN, LEFT, RIGHT
} Direction;

typedef struct SnakePart SnakePart;

struct SnakePart {
  int x, y;
  SnakePart* previous;
  SnakePart* next;
};

typedef struct Snake {
  int length;
  struct SnakePart* head;
  struct SnakePart* tail;
  Direction dir;
} Snake;

/* Creates a new part and makes it the new head, 
 * positioned in the target position of the snake.
 * Assumes target position is inside the map.
 * Assumes the snake has at least a head. */
void growSnake(Snake* snake);

/* Moves the snake to the target direction.
 * Assumes it exists on the map */
void moveSnake(Snake* snake);

void destroySnake(Snake* snake);

/* Creates the snake of the start of 
 * the game (length 3) */
Snake* initSnake();

#endif // SNAKE_H
