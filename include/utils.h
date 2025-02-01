#ifndef UTILS_H
#define UTILS_H
#include <SDL2/SDL_timer.h>

typedef void (*TimeOutCallback)(void);

typedef struct {
  float elapsedTime;
  float timerDuration;
  TimeOutCallback timeoutCallback;
} Timer;

/* Increments elapsedTime of a timer, or 
 * restarts and calls callback if reaches timerDuration */
void updateTimer(Timer* timer, float dt);

/* Returns the time between two frames in seconds */
float calculateDeltaTime(Uint32 *frameStart);

#endif // UTILS_H
