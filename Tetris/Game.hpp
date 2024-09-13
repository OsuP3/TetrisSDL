#ifndef Game_hpp
#define Gamme_hpp

#include <math.h>
#include "SDL.h"
#include <iostream>
#include "Piece.hpp"

class Game
{
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void update();

	void handleEvents();

	void render();

	void clean();

	bool running() { return isRunning; }

private:
	int width, height;
	bool isRunning;
	SDL_Surface* tile_map_surface;
	SDL_Texture* tile_texture;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int cnt=0;
	SDL_Rect tile[10][20];
	int tilemap[10][20];
	SDL_Rect select_tile1;
	SDL_Rect select_tile2;
	SDL_Rect select_tile3;
	SDL_Rect select_tile4;
	SDL_Rect select_tile5;
	SDL_Rect select_tile6;
	SDL_Rect select_tile7;
	SDL_Rect select_tile8;
	Piece newpiece;


};

#endif //Game_hpp