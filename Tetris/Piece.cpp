#include "Piece.hpp"


Piece::Piece() {
	return;
}

void Piece::init(int(&tilemap)[10][20]) {


	srand(time(NULL));

	std::string choices[7] = { "L","J", "Z", "S", "T", "O", "I" };

	int pick = rand() % 7 + 2;
	pieceType = pick;

	Occupying = {};
	switch (pick)
	{
	case 5://L

		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 4, 2 });
		Occupying.push_back({ 5, 2 });
		break;
	case 8://J
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 4, 2 });
		Occupying.push_back({ 3, 2 });
		break;
	case 7://Z
		Occupying.push_back({ 3, 0 });
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 5, 1 });
		break;
	case 2://S
		Occupying.push_back({ 5, 0 });
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 3, 1 });
		break;
	case 6://T
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 5, 1 });
		Occupying.push_back({ 3, 1 });
		break;
	case 4://O
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 5, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 5, 1 });
		break;
	case 3://I
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 4, 2 });
		Occupying.push_back({ 4, 3 });
		break;
	default:
		break;
	}

	for (std::vector<int> tile : Occupying) {
		tilemap[tile.at(0)][tile.at(1)] = pick;
	}

	return;
}

void Piece::manifest(int(&tilemap)[10][20]) {
	for (std::vector<int> tile : Occupying) {
		tilemap[tile.at(0)][tile.at(1)] = pieceType;
	}
}

void Piece::movedown(int(&tilemap)[10][20]) {
	for (std::vector<int> tile : Occupying) {
		if (tile.at(1) + 1 >=20 || (tilemap[tile.at(0)][tile.at(1) + 1] != 1 && tilemap[tile.at(0)][tile.at(1) + 1] != pieceType)) {
			this->init(tilemap);
			return;
		}
	}

	for (std::vector<int> tile : Occupying) {
		tilemap[tile.at(0)][tile.at(1)] = 1;
	}

	Occupying.at(0).at(1) = Occupying.at(0).at(1) + 1;
	Occupying.at(1).at(1) = Occupying.at(1).at(1) + 1;
	Occupying.at(2).at(1) = Occupying.at(2).at(1) + 1;
	Occupying.at(3).at(1) = Occupying.at(3).at(1) + 1;

}