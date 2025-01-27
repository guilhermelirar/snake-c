#include <SDL2/SDL.h>
#include "include/game.h"


int main(int argc, char *argv[]) {
  Game *game = createGame();

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer); 
  // Updates window
  SDL_RenderPresent(game->renderer);

  SDL_Delay(5000); 

  destroyGame(game);
  return 0;
}
