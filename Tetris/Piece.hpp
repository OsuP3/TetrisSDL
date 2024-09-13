#ifndef PIECE_HPP
#define PIECE_HPP

#include <math.h>
#include "SDL.h"
#include <iostream>
#include <vector>


class Piece {
public:
	Piece();
	void init(int(&tilemap)[10][20]);
	void movedown(int(&tilemap)[10][20]) {
		for (std::vector<int> tile : Occupying) {
			tilemap[tile.at(0)][tile.at(1)] = 1;
		}

		Occupying.at(0).at(1) = Occupying.at(0).at(1) + 1;
		Occupying.at(1).at(1) = Occupying.at(1).at(1) + 1;
		Occupying.at(2).at(1) = Occupying.at(2).at(1) + 1;
		Occupying.at(3).at(1) = Occupying.at(3).at(1) + 1;

	}
	void manifest(int(&tilemap)[10][20]);




private:

	std::vector<std::vector<int>> Occupying;

	int pieceType;
	
};






#endif // !PIECE_HPP
