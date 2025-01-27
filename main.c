#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[]) {
  // Initializing SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error when initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  // Window
  SDL_Window *window = SDL_CreateWindow(
      "SNAKE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Error when creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Creating renderer 
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  if (!renderer) {
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
 
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Updates window
  SDL_RenderPresent(renderer);

  SDL_Delay(5000); 

  // Free resources
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
