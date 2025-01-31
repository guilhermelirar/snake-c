#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL_timer.h>

typedef void (*TimeOutCallback)(void);

typedef struct {
  float elapsedTime;
  float timerDuration;
  TimeOutCallback timeoutCallback;
} Timer;

void updateTimer(Timer* timer, float dt);

float calculateDeltaTime(Uint32 *frameStart);

#endif // UTILS_H
