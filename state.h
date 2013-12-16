#pragma once

extern bool _running;

enum player_state {
	GROUND=0, JUMP_1_START, JUMP_1, JUMP_2_START, JUMP_2, SLIDE, HOVER, HOVER_FALL
};
//200ms is threshold for 'tap'
const static unsigned tap_threshold = 11; //10 frames * 16ms/frame
enum keypress_length {
	NONE=0, TAP, HOLD
};

//taken from sdl tutorial
struct fps_t {
	int old, last, fps, frames;
	float speed;

	fps_t() : old(0), last(0), fps(0), frames(0), speed(0.f) {}
	void update() {
		int t = SDL_GetTicks();
		if(old+1000 < t) { //update frame per second metric
			old = t;
			fps = frames;
			frames = 0;
		}
		speed = ((t-last)/1000.f) * 60.f; //target fps
		last = t;
		frames++;
	}
};

class State {
public:
	fps_t fps;
	player_state ps;
	bool button_pressed;
	unsigned button_count; //count num of frames to move between 'tap' and 'hold' modes
	keypress_length button_state;
	long long frame;
	int hold_time;

	State() {
		//set everything to 0
		button_pressed = false;
		button_count = 0;
		button_state = NONE;
		frame = 0;
		hold_time = 0;
	}

	void update() {
		fps.update();
		if(button_pressed) {
			if(++button_count > tap_threshold) {
				button_state = HOLD;
				hold();
			}
		}
		frame++;
	}

	bool active_frame() {
		return true;
		//return frame % 60 == 0;
	}

	void tap() {
		switch(ps) {
			case GROUND: ps = JUMP_1_START; break;
			case JUMP_1: ps = JUMP_2_START; break;
			default: {}
		}
	}

	void hold() {
		switch(ps) {
			case GROUND: ps = SLIDE; break;
			case JUMP_1: 
			case JUMP_2: ps = HOVER; break;
			default: {}
		}
	}
	void release() {
		switch(ps) {
			case SLIDE: ps = GROUND; break;
			case HOVER: ps = HOVER_FALL; break;
			default: {}
		}
	}

	void keydown(SDLKey sym, SDLMod mod, Uint16 unicode) {
		//printf("state keydown\n");
		switch(sym) {
		//case SDLK_z: { button_pressed = true; button_state = TAP; hold_time = SDL_GetTicks(); break; }
		case SDLK_z: tap(); break;
		case SDLK_q: _running = false; break;
		default: {}
		}

	}
	void keyup(SDLKey sym, SDLMod mod, Uint16 unicode) {
		//printf("state keyup\n");
		switch(sym) {
#if 0
		case SDLK_z: { button_pressed = false; button_count = 0; if(button_state == TAP) { tap(); } else { release(); } button_state = NONE; /*printf("z hold time: %d\n", SDL_GetTicks()-hold_time);*/ break; }
#endif
		default: {}
		}
	}

	void mouseup() {

	}
	void mousedown() {
		tap();
	}
};
