#pragma once
#include "globals.h"
#include "player.h"


struct Tile {
	static const unsigned w = 40;
	//num pixels from the bottom edge of the screen
	//negative values represent no floor or ceiling
	int floor, ceiling;
	void genrand() {
		floor = 20 + rand()%3*20;
		ceiling = (rand()%4 == 0) ? SCREEN_HEIGHT-10 : -1;
	}
};

class World { 
public:
	int left; //how many pixels have scrolled from the current tile
	static const unsigned num_tiles = 16;
	Tile map[num_tiles]; //wrap around map
	int map_curr; //current spot in the map
	SDL_Surface *w;

	void init() {
		for(int z=0;z<num_tiles;z++) {
			map[z].genrand();
		}
	}
	void reset() { init(); }
	void update() {
		if(st.active_frame()) {
			if(++left >= Tile::w) {
				left = left % Tile::w;
				map[map_curr].genrand();
				map_curr = (map_curr + 1) % num_tiles;
			}
		}
	}
	//draw onto world, blit onto screen surface
	void draw() {
		// draw lines representing tiles

		SDL_Rect r = {0, 0, Tile::w, 2};
		SDL_Rect v = {0, 0, 2, 10};
		int id;
		for(int z=0;z<num_tiles;z++) {
			id=(z+map_curr)%num_tiles;
			const Tile &t = map[id];
			if(z == 0) {
				r.x = 0;
				r.w = Tile::w-left + 2;
			} else {
				r.x = -left + z*Tile::w;
				r.w = Tile::w + 2;
			}
			if(t.floor >= 0) {
				r.y = SCREEN_HEIGHT - t.floor;
				SDL_FillRect(screen, &r, SDL_MapRGBA(screen->format, 0xff, 0xff, 0xff, 0xff));

				//draw vertical line to next piece
				int oh = SCREEN_HEIGHT - map[(id+1)%num_tiles].floor;
				v.x = r.x + Tile::w - (z==0?left:0);
				v.y = oh > r.y ? r.y : oh;
				v.h = oh > r.y ? oh-r.y : r.y-oh;
				SDL_FillRect(screen, &v, SDL_MapRGBA(screen->format, 0xff, 0xff, 0xff, 0xff));
			}
			if(t.ceiling >= 0) {
				r.y = SCREEN_HEIGHT - t.ceiling;
				SDL_FillRect(screen, &r, SDL_MapRGBA(screen->format, 0x77, 0x77, 0x77, 0xff));
			}
		}

	}

	void collide(Player *p) {
		float left_h = height(Player::xpos);
		float right_h = height(Player::xpos+Player::w-1);

		//wall collision
		if(left_h < right_h) {
			//printf("left wall < right wall: %f < %f. player: %f [+h %f]\n", left_h, right_h, p->y, p->y-Player::h);
			if(p->y-Player::h < right_h - 4) //4 is to add a bit of leeway when landing - helps when you land on a corner
				_game_state = SCORE_SCREEN;
		}

		//floor collision
		p->collide_floor(left_h > right_h ? left_h : right_h);

	}

	float height(float x) const {
		unsigned id = (int)(x+left) / Tile::w;
		return map[(map_curr + id)%num_tiles].floor;
	}
};
