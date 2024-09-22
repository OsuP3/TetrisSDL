#include "Piece.hpp"
#include <algorithm>



	
Piece::Piece() {
	return;
}


void Piece::init(int(&tilemap)[10][20]) {
	srand(time(NULL));

	//int lol[2][2] = { {1,2}, {1,3}};

	std::string choices[7] = { "L","J", "Z", "S", "T", "O", "I" };

	pieceType = rand() % 7 + 2;
	//pieceType = 5;
	Occupying = {};
	switch (pieceType)
	{
	case 2://S
		Occupying.push_back({ 5, 0 });
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 3, 1 });

		break;
	case 3://I
		Occupying.push_back({ 3, 0 });
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 5, 0 });
		Occupying.push_back({ 6, 0 });

		break;
	case 4://O
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 5, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 5, 1 });

		break;
	case 5://L
		Occupying.push_back({ 3, 1 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 5, 1 });
		Occupying.push_back({ 5, 0 });
		break;
	case 6://T
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 5, 1 });
		Occupying.push_back({ 3, 1 });
		break;
	case 7://Z
		Occupying.push_back({ 3, 0 });
		Occupying.push_back({ 4, 0 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 5, 1 });
		break;
	case 8://J
		Occupying.push_back({ 3, 0 });
		Occupying.push_back({ 3, 1 });
		Occupying.push_back({ 4, 1 });
		Occupying.push_back({ 5, 1 });

		break;
	default:
		break;
	}

	orientation = 1;
	manifest(tilemap);

	return;
}

void Piece::checkclear(int(&tilemap)[10][20]) {
	bool lineclear;
	for (int y = 0; y < 20; y++) {
		lineclear = true;
		for (int x = 0; x < 10; x++) {
			if (tilemap[x][y] == 1) {//check rows for clears
				lineclear = false;
				break;
			}
		}
		if (lineclear) {
			std::cout << "Line Clear!" << std::endl;
			for (int x = 0; x < 10; x++) {//clear line
				tilemap[x][y] = 1;

				for (int y2 = y; y2 > 0; y2--) {//bring column down after clear
					tilemap[x][y2] = tilemap[x][y2-1];
				}

			}
			
		}

	}

}

void Piece::manifest(int(&tilemap)[10][20]) {
	for (std::vector<int> tile : Occupying) {
		tilemap[tile.at(0)][tile.at(1)] = pieceType;
	}
}

void Piece::movedown(int(&tilemap)[10][20]) {

		for (std::vector<int> tile : Occupying) {
			const int x = tile.at(0);
			const int y = tile.at(1);

			if (y + 1 >= 20 || (tilemap[x][y + 1] != 1 && !(std::find(Occupying.begin(), Occupying.end(), std::vector<int> {x, y + 1}) != Occupying.end()))) {//touches floor || (not empty tile && not user piece)
				checkclear(tilemap);
				this->init(tilemap);//hits floor -> new piece
				return;
			}
		}

		{//remove old piece location & then move to new location
			for (std::vector<int> tile : Occupying) {
				tilemap[tile.at(0)][tile.at(1)] = 1;
			}
			Occupying.at(0).at(1) = Occupying.at(0).at(1) + 1;
			Occupying.at(1).at(1) = Occupying.at(1).at(1) + 1;
			Occupying.at(2).at(1) = Occupying.at(2).at(1) + 1;
			Occupying.at(3).at(1) = Occupying.at(3).at(1) + 1;
		}

	

}

void Piece::moveside(int(&tilemap)[10][20], int side) {

	for (std::vector<int> tile : Occupying) {
		const int x = tile.at(0);
		const int y = tile.at(1);

		if ((x + side > 10 && x + side < 0) || (tilemap[x + side][y] != 1 && !(std::find(Occupying.begin(), Occupying.end(), std::vector<int> {x + side, y}) != Occupying.end()))) {//touches wall || (touches not empty tile && touches not user piece)
			std::cout << "Hit wall!" << std::endl;
			return;
		}
	}

	{//remove old piece location & then move to new location
		for (std::vector<int> tile : Occupying) {
			tilemap[tile.at(0)][tile.at(1)] = 1;
		}
		Occupying.at(0).at(0) = Occupying.at(0).at(0) + side;
		Occupying.at(1).at(0) = Occupying.at(1).at(0) + side;
		Occupying.at(2).at(0) = Occupying.at(2).at(0) + side;
		Occupying.at(3).at(0) = Occupying.at(3).at(0) + side;
	}
}

void Piece::instadrop(int(&tilemap)[10][20]) {

	for (int y = 0; y < 20; y++) {
		for (std::vector<int> tile : Occupying) {
			const int x = tile.at(0);
			const int y = tile.at(1);

			if (y + 1 >= 20 || (tilemap[x][y + 1] != 1 && !(std::find(Occupying.begin(), Occupying.end(), std::vector<int> {x, y + 1}) != Occupying.end()))) {//touches floor || (not empty tile && not user piece)
				checkclear(tilemap);
				this->init(tilemap);//hits floor -> new piece
				return;
			}
		}

		{//remove old piece location & then move to new location
			for (std::vector<int> tile : Occupying) {
				tilemap[tile.at(0)][tile.at(1)] = 1;
			}
			Occupying.at(0).at(1) = Occupying.at(0).at(1) + 1;
			Occupying.at(1).at(1) = Occupying.at(1).at(1) + 1;
			Occupying.at(2).at(1) = Occupying.at(2).at(1) + 1;
			Occupying.at(3).at(1) = Occupying.at(3).at(1) + 1;
		}
		manifest(tilemap);//IMPORTANT!!!!!!!!!
	}
}

void Piece::rotate(int(&tilemap)[10][20]) {
	std::vector<std::vector<int>> newOrientation = Occupying;
	int tilenum = 0;
	for(int i = 0; i < 4; i++){
		newOrientation.at(i).at(0) += operations[pieceType - 2][orientation - 1][tilenum][0];
		newOrientation.at(i).at(1) += operations[pieceType - 2][orientation-1][tilenum][1];
		if (newOrientation.at(i).at(0) >= 10 || newOrientation.at(i).at(0) < 0) { return;}
		if (newOrientation.at(i).at(1) >= 20 || newOrientation.at(i).at(1) < 0) { return;}

		tilenum++;
	}
	//remove old piece location & then move to new location
		for (std::vector<int> tile : Occupying) {
			tilemap[tile.at(0)][tile.at(1)] = 1;
		}
		if (orientation == 4) { orientation = 1; }
		else { orientation++;}
	Occupying = newOrientation;
	manifest(tilemap);
}
/*
 0 1 0 0
 0 1 0 0
 0 1 1 0
 0 0 0 0


*/