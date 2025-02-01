#include "utils.h"

void updateTimer(Timer *timer, float dt) {
  timer->elapsedTime += dt;
  if (timer->elapsedTime >= timer->timerDuration) {
    timer->elapsedTime = 0.0f;
    timer->timeoutCallback();
  } 
}

float calculateDeltaTime(Uint32 *frameStart) {
  Uint32 newFrameStart = SDL_GetTicks();
  float dt = (newFrameStart - (*frameStart)) / 1000.0f;
  *frameStart = newFrameStart;
  return dt;
}
