#pragma once
#include <SDL/SDL.h>

#if EMSCRIPTEN
#include <emscripten.h>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#define SDLMod unsigned short //fails to compile without this for some reason [[shrug]]
#endif

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

extern SDL_Surface *screen;
enum game_state_t {
	LOADING=0, START_SCREEN, IN_GAME, SCORE_SCREEN, QUIT
};
extern game_state_t _game_state;

static const float gravity = .25;
static const float epsilon = 1e-6;

#include "state.h"
extern State st;
