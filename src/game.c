#include "../include/game.h"
#include "../include/snake.h"
#include "../include/utils.h"
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
  initMap();
  game->snake = initSnake();

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
  SDL_Quit();
}

void initMap() {
  Game* game = getGame();
  // Initializing tilemap with void
  for (int y = 0; y < SCREEN_HEIGHT / TILE_SIZE; y++) {
    for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; x++) {
      game->map[y][x] = VOID;
    }
  }
}


void drawGame() {
  Game* game = getGame();
  SDL_Renderer *renderer = game->renderer;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Used to rendering tiles
  SDL_Rect rect = {0, 0, TILE_SIZE, TILE_SIZE};

  // For each tile
  for (int y = 0; y < SCREEN_HEIGHT / TILE_SIZE; y++) {
    for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; x++) {
      // Position of the rect
      rect.y = TILE_SIZE * y;
      rect.x = TILE_SIZE * x;

      switch (game->map[y][x]) {
        case VOID: // Grid-like 
          SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
          SDL_RenderDrawRect(renderer, &rect);
        break;
        case SNAKE: // White
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
    if (event.type == SDL_QUIT) {
      game->status = QUIT_REQUESTED;
      return;
    }

    if (event.type == SDL_KEYDOWN) {
      // Snake movement
      switch (event.key.keysym.sym) {
        case (SDLK_UP): {
          game->snake->dir = UP;
          break;
        }
        case (SDLK_DOWN): {
          game->snake->dir = DOWN;
          break;
        }
        case (SDLK_LEFT): {
          game->snake->dir = LEFT;
          break;
        }
        case (SDLK_RIGHT): {
          game->snake->dir = RIGHT;
          break;
        }  
        default:
          break;
      }

      if (event.key.keysym.sym == SDLK_SPACE) {
        // Pause if running, resume if paused
        game->status = game->status == RUNNING ? PAUSED : RUNNING;
      }
    }
  }
}

void update() {
  Snake *snake = getGame()->snake;
  Direction dir = snake->dir;
  int headX = snake->head->x, headY = snake->head->y;

  // Snake collided with the limits of the map
  if ((headX == 0 && dir == LEFT) ||
      (headX == SCREEN_WIDTH / TILE_SIZE - 1 && dir == RIGHT) ||
      (headY == 0 && dir == UP) ||
      (headY == SCREEN_HEIGHT / TILE_SIZE - 1 && dir == DOWN)) {
    getGame()->status = QUIT_REQUESTED;
    return;
  }

  TileStatus snakeTargetStatus =
      getGame()->map[headY + (dir == DOWN) - (dir == UP)]
                    [headX + (dir == RIGHT) - (dir == LEFT)];

  if (snakeTargetStatus == SNAKE) {
    getGame()->status = QUIT_REQUESTED;
    return;
  } 

  moveSnake(snake);
}

void run() {
  Game* game = getGame();
  game->status = RUNNING;

  Timer timer = {0.0f, .3f, update};
  Uint32 frameStart = 0;
  float dt;
  while (game->status != QUIT_REQUESTED) {
    dt = calculateDeltaTime(&frameStart);
    
    handleInput();

    if (game->status == RUNNING) {
      updateTimer(&timer, dt);
    }

    drawGame();
    SDL_Delay(30);
  }
}
