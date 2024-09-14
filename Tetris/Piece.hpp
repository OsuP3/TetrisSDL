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
	void movedown(int(&tilemap)[10][20]);
	void manifest(int(&tilemap)[10][20]);




private:

	std::vector<std::vector<int>> Occupying;

	int pieceType;
	
};






#endif // !PIECE_HPP
