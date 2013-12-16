#include <SDL/SDL.h>
#include "globals.h"
#include "world.h"
#include "player.h"

SDL_Surface *screen;
World world;
State st;
Player p;
SDL_Event e;

game_state_t _game_state;

bool init();
void event(SDL_Event *e);
void update();
void draw();
void cleanup();

void event(SDL_Event *e) {
	switch(e->type) {
		case SDL_KEYDOWN: { st.keydown(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.unicode);  break; }
		case SDL_KEYUP: { st.keyup(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.unicode); break; }
		case SDL_MOUSEBUTTONDOWN: st.mousedown(); break;
		case SDL_MOUSEBUTTONUP: st.mouseup(); break;
		case SDL_QUIT: _game_state = QUIT;
	}
}

void update() {
	// move player and world point. also check for collisions on player move
	st.update(); //timing / fps update
	world.update(); //shift world position
	world.collide(&p);
	p.update(); //check state change [jump / slide] / animation / move player
}

void draw() {
	SDL_FillRect(screen, 0, SDL_MapRGBA(screen->format, 0, 0, 0, 0xff)); //clear to black
	world.draw();
	p.draw();
}

// init sdl and other globals
bool init() {
	_game_state = LOADING;
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stdout,"failed to init sdl\n"); return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
	if(screen == 0) {
		fprintf(stdout,"failed to init screen\n"); return false;
	}

	world.reset();
	p.reset();
	return true;
}

void cleanup() {
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void loop() {
	if(_game_state == SCORE_SCREEN) {
		printf("you hit a wall =(\n");
		_game_state = IN_GAME;
		world.reset();
		p.reset();
	}
	while(SDL_PollEvent(&e)) event(&e);
	update();
	draw();
	SDL_Flip(screen);
}

int main() {
	printf("ludumdare28 - \'you only have one...\' button!\npress \'z\' to jump\n");

	if(!init()) {
		fprintf(stdout, "an error occurred during init, exiting\n"); return -1;
	}

	_game_state = IN_GAME;
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(loop, 0, 1);
#else
	int t_start;
	while(_game_state != QUIT) {
		t_start = SDL_GetTicks();
		loop();
		SDL_Delay(16-(SDL_GetTicks()-t_start));
	}
#endif

	cleanup(); //SDL_FreeSurface / SDL_Quit
	return 0;
}

