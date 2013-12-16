#pragma once
#include "globals.h"

//enum player_state {
//	GROUND=0, JUMP_1_START, JUMP_1, JUMP_2_START, JUMP_2, SLIDE, AIR_DROP, HOVER, HOVER_FALL
//};

class Player {
public:
	static const int xpos = 50.f;
	static const int h = 20;
	static const int w = 10;
	float y, yv;

	Player() : y(100.f), yv(0.f) { }

	void update() {
		//player state member in state
		switch(st.ps) {
			case HOVER: yv = 0; break; //infinite hover for now
			case SLIDE:
			case GROUND: break; //do nothing, y-axis doesnt change - TODO: animation change
			case JUMP_2_START:
			case JUMP_1_START: yv = 4; break; //vel[1] = 1; break; //add 'jump' to velocity
			case HOVER_FALL:
			case JUMP_2:
			case JUMP_1: {
							 yv += -gravity * st.fps.speed;
							 y += yv * st.fps.speed;
							 break;
						 }
		}
		if(st.ps == JUMP_1_START) st.ps = JUMP_1;
		else if(st.ps == JUMP_2_START) st.ps = JUMP_2;
		else if(st.ps == HOVER_FALL && y <= 0) st.ps = GROUND;

		//printf("player: y: %f, state: %d\n", y, st.ps);
	}
	void draw() const {
		SDL_Rect r = {xpos, SCREEN_HEIGHT - y, w, h};
		if(st.ps == SLIDE || st.ps == HOVER) {
			r.w = h;
			r.h = w;
			r.y += w;
		}
		// motion blur!
		if(st.ps == JUMP_1 || st.ps == JUMP_2) {
			r.x -= 2; r.y -= (yv > 0) ? -2 : 2;
			SDL_FillRect(screen, &r, SDL_MapRGBA(screen->format, 0x00, 0x33, 0x66, 0xff));
			r.x += 2; r.y += (yv > 0) ? -2 : 2;
		}
		SDL_FillRect(screen, &r, SDL_MapRGBA(screen->format, 0x00, 0x77, 0xaa, 0xff));
	}

	void collide_floor(float fy) {
		if((st.ps == GROUND || st.ps == SLIDE) && fy > 0 && (y-h < fy-epsilon || y-h > fy+epsilon)) {
			st.ps = JUMP_1; //falling mode
		} else if((st.ps == JUMP_1 || st.ps == JUMP_2 || st.ps == HOVER_FALL) && yv < 0 && fy > 0 && y-h < fy-epsilon) {
			y = fy+h + epsilon; yv=0.f;
			st.ps = GROUND;
		}
	}
	void reset() {

	}
};
