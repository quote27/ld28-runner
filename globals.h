#pragma once
#include <SDL/SDL.h>

#if EMSCRIPTEN
#include <emscripten.h>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#define SDLMod unsigned short //fails to compile without this for some reason [[shrug]]
#endif

//#include "vec.h"
#include "state.h"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

extern SDL_Surface *screen;
extern bool _running;
extern bool _lost;
extern State st;

static const float gravity = .25;
static const float epsilon = 1e-6;
