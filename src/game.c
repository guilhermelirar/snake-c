#include "game.h"
#include "snake.h"
#include "utils.h"
#include "time.h"
#include <stdlib.h>

Game* getGame() {
  static Game* game = NULL;
  if (game != NULL) {
    return game;
  }

  // Initializing SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error when initializing SDL: %s\n", SDL_GetError());
    return NULL;
  }

  // Window
  SDL_Window *window = SDL_CreateWindow(
      "SNAKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Error when creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return NULL;
  }

  // Creating renderer 
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  if (!renderer) {
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return NULL;
  }

  // Creating a game struct
  game = (Game*)malloc(sizeof(Game));
  if (!game) {
    printf("Error when creating window: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
  }

  // Setting members
  game->window = window;
  game->renderer = renderer;
  game->snake = NULL;

  srand(time(NULL));

  return game;
}

void destroyGame() {
  Game* game = getGame();
  if (game->renderer) {
    SDL_DestroyRenderer(game->renderer);
  }

  if (game->window) {
    SDL_DestroyWindow(game->window); 
  }

  if (game->snake) {
    destroySnake(game->snake); 
  }

  free(game);
  SDL_Quit(); // Quit SDL subsystems
}

void initMap() {
  Game* game = getGame();
  // Initializing tilemap with void
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      game->map[y][x] = VOID;
    }
  }
}


void spawnFruit() {
  int availableTiles = MAP_HEIGHT * MAP_WIDTH - getGame()->snake->length;

  if (availableTiles == 0) {
    return;
  }

  GameMap *map = &getGame()->map;
  int i = rand() % availableTiles;

  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if ((*map)[y][x] == VOID) {
        if (i-- == 0) {
          (*map)[y][x] = FRUIT;
          return;
        }
      }
    }
  }
}

void drawGame() {
  Game *game = getGame();
  SDL_Renderer *renderer = game->renderer;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Used to rendering tiles
  SDL_Rect rect = {0, 0, TILE_SIZE, TILE_SIZE};

  // For each tile
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      // Position of the rect
      rect.y = TILE_SIZE * y;
      rect.x = TILE_SIZE * x;

      switch (game->map[y][x]) {
      case VOID: // Grid-like
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 15);
        SDL_RenderDrawRect(renderer, &rect);
        break;
      case SNAKE: // Green
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        break;
      case FRUIT: // Red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        break;
      }
    }
  }

  SDL_RenderPresent(renderer);
}

void handleInput() {
  Game* game = getGame();
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
      game->status = QUIT_REQUESTED;
      return;
    }

    if (event.key.keysym.sym == SDLK_SPACE) {
      // Pause if running, resume if paused
      game->status = game->status == RUNNING ? PAUSED : RUNNING;
    }

    Direction *dir = &game->snake->dir;
    Direction newDir = *dir;
    if (event.type == SDL_KEYDOWN) {
      // Snake movement
      switch (event.key.keysym.sym) {
        case (SDLK_UP): {
          newDir = UP;
          break;
        }
        case (SDLK_DOWN): {
          newDir = DOWN;
          break;
        }
        case (SDLK_LEFT): {
          newDir = LEFT;
          break;
        }
        case (SDLK_RIGHT): {
          newDir = RIGHT;
          break;
        }  
        default:
          break;
      }

      *dir = newDir;
    }
  }
}

void update() {
  Snake *snake = getGame()->snake;
  Direction dir = snake->dir;
  Position headPos = snake->head->pos;

  // Target position
  Position newPos = {headPos.x + (dir == RIGHT) - (dir == LEFT),
                     headPos.y + (dir == DOWN) - (dir == UP)};

  // Snake collided with map limit
  if (newPos.x < 0 || newPos.x == MAP_WIDTH || newPos.y < 0 ||
      newPos.y == MAP_HEIGHT) {
    getGame()->status = RESET_REQUESTED;
    return;
  }

  // Checking the status of that position
  TileStatus snakeTargetStatus = getGame()->map[newPos.y][newPos.x];

  // Target status is part of Snake
  if (snakeTargetStatus == SNAKE) {
    // Snake should not die if new direction cancels previous
    if (POS_EQUAL(snake->head->next->pos, newPos)) {
      switch (dir) {
        case UP:
          snake->dir = DOWN;
        break;
        case DOWN:
          snake->dir = UP;
        break;
        case RIGHT:
          snake->dir = LEFT;
        break;
        case LEFT:
          snake->dir = RIGHT;
      }

      // Snake will update as it has the previous direction
      return update();
    }

    // Snake died
    getGame()->status = RESET_REQUESTED;
    return;
  }

  // Sake will grow
  if (snakeTargetStatus == FRUIT) {
    growSnake(snake);
    spawnFruit();
    return;
  }

  // Snake will just move
  moveSnake(snake);
}

void startGame() {
  Game* game = getGame();
  game->status = RUNNING;
  initMap();
  if (game->snake) {
    destroySnake(game->snake);
  }
  game->snake = initSnake();
  spawnFruit();
}

void run() {
  Game* game = getGame();
  startGame();

  // Call update every 0,3 seconds
  Timer timer = {0.0f, .3f, update};
  Uint32 frameStart = 0; 
  float dt; // seconds between frames
  while (game->status != QUIT_REQUESTED) {
    if (game->status == RESET_REQUESTED) {
      timer.elapsedTime = 0.0f;
      startGame();
    }

    dt = calculateDeltaTime(&frameStart);
    
    handleInput();

    if (game->status == RUNNING) {
      updateTimer(&timer, dt);
    }

    drawGame();
    SDL_Delay(30);
  }
}
