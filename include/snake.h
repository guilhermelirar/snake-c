#ifndef SNAKE_H
#define SNAKE_H

typedef enum {
  TOP, DOWN, LEFT, RIGHT
} Direction;

struct SnakePart {
  int x, y;
  struct SnakePart* previous;
};

typedef struct {
  int length;
  struct SnakePart* head;
  struct SnakePart* tail;
  Direction dir;
} Snake;

// Pop tail (for moving)
struct SnakePart* popTail(Snake* snake);
// New snake part
struct SnakePart* newPart(int x, int y, struct SnakePart* previous);
// Free resources
void destroySnake(Snake* snake);
// Creates snake with 3 parts
Snake* createStartSnake();

#endif // SNAKE_H
