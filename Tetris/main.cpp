#include <SDL.h>
#include "Game.hpp"


Game* game = nullptr;

int main(int argc, char* argv[]) {
	game = new Game();
	game->init("Osu's Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,640, false);

	while (game->running()) {
		try {
			game->handleEvents();
			game->update();
			game->render();
		}
		catch (GameResultException* e) {
			game->render();
			std::cout << e->get_result() << "\n";
			break;
		}
	}

	game->clean();

	return 0;
}