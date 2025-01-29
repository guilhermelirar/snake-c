#include <SDL2/SDL.h>
#include "include/game.h"

int main(int argc, char *argv[]) {
  Game *game = createGame();
  run(game);
  destroyGame(game);
  return 0;
}
