#include <SDL2/SDL.h>
#include "include/game.h"

int main(int argc, char *argv[]) {
  Game *game = createGame();

  render(game);

  SDL_Delay(5000); 

  destroyGame(game);
  return 0;
}
