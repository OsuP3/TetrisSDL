#include "Game.hpp"


Game::Game() {}

Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	this->width = width;
	this->height = height;
	if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!......" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		tile_map_surface = SDL_LoadBMP("./assets/tile.bmp");
		if (renderer && tile_map_surface){
			tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
			SDL_FreeSurface(tile_map_surface);

			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 20; y++) {
					tilemap[x][y] = 1;
				}
			}

			for (int x = 0; x < 10; x++) {
				for (int y = 0; y < 20; y++) {
					tile[x][y].x = x * 32;
					tile[x][y].y = y * 32;
					tile[x][y].w = 32;
					tile[x][y].h = 32;
				}
			}

			select_tile1.x = 0;
			select_tile1.y = 0;
			select_tile1.w = 32;
			select_tile1.h = 32;

			select_tile2.x = 32;
			select_tile2.y = 0;
			select_tile2.w = 32;
			select_tile2.h = 32;

			select_tile3.x = 64;
			select_tile3.y = 0;
			select_tile3.w = 32;
			select_tile3.h = 32;

			select_tile4.x = 96;
			select_tile4.y = 0;
			select_tile4.w = 32;
			select_tile4.h = 32;

			select_tile5.x = 0;
			select_tile5.y = 32;
			select_tile5.w = 32;
			select_tile5.h = 32;

			select_tile6.x = 32;
			select_tile6.y = 32;
			select_tile6.w = 32;
			select_tile6.h = 32;

			select_tile7.x = 64;
			select_tile7.y = 32;
			select_tile7.w = 32;
			select_tile7.h = 32;

			select_tile8.x = 96;
			select_tile8.y = 32;
			select_tile8.w = 32;
			select_tile8.h = 32;


			newpiece.init(tilemap);

			std::cout << "Renderer, Grid, created!" << std::endl;
		}
		isRunning = true;

	}
	else {
		isRunning = false;
	}
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type){
	
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_RIGHT:
					std::cout << "right key was pressed"<<std::endl;
					break;
				case SDLK_LEFT:
					std::cout << "Left key was pressed" << std::endl;
					break;
				case SDLK_DOWN:
					newpiece.movedown(tilemap);
					std::cout << "Down key was pressed" << std::endl;
					break;
				case SDLK_UP:
					std::cout << "Up key was pressed" << std::endl;
					break;
				default:
					break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				std::cout << "right key was unpressed" << std::endl;
				break;
			case SDLK_LEFT:
				std::cout << "Left key was unpressed" << std::endl;
				break;
			case SDLK_DOWN:
				std::cout << "Down key was unpressed" << std::endl;
				break;
			case SDLK_UP:
				std::cout << "Up key was unpressed" << std::endl;
				break;
			default:
				break;
			}
			break;

		default:
			break;
	}
	newpiece.manifest(tilemap);
}

void Game::update() {	
	//increase time
	//check if a line is cleared
}

void Game::render(){
	//SDL_SetRenderDrawColor(renderer, 0x66,0x66,0xBB,0xFF);
	SDL_RenderClear(renderer);
	SDL_Delay(20);


	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 20; y++) {
			switch (tilemap[x][y])
			{
			case 1:
				SDL_RenderCopy(renderer, tile_texture, &select_tile1, &tile[x][y]);//tile 1 is an empty cell
				break;
			case 2:
				SDL_RenderCopy(renderer, tile_texture, &select_tile2, &tile[x][y]);//tile 2 
				break;
			case 3:
				SDL_RenderCopy(renderer, tile_texture, &select_tile3, &tile[x][y]);//tile 3
				break;
			case 4:
				SDL_RenderCopy(renderer, tile_texture, &select_tile4, &tile[x][y]);//tile 4 
				break;
			case 5:
				SDL_RenderCopy(renderer, tile_texture, &select_tile5, &tile[x][y]);//tile 5 
				break;
			case 6:
				SDL_RenderCopy(renderer, tile_texture, &select_tile6, &tile[x][y]);//tile 6 
				break;
			case 7:
				SDL_RenderCopy(renderer, tile_texture, &select_tile7, &tile[x][y]);//tile 7 
				break;
			case 8:
				SDL_RenderCopy(renderer, tile_texture, &select_tile8, &tile[x][y]);//tile 8 
				break;
			default:
				break;
			}
			
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned"<<std::endl;
}