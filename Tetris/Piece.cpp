#include "Piece.hpp"
	
Piece::Piece() {
	return;
}


void Piece::init(int(&tilemap)[10][20]) {
	srand(time(NULL));
	shadowOccupying = {};
	// "L","J", "Z", "S", "T", "O", "I" 
	if(choicePool.size() == 0)
		choicePool = { 2 ,3, 4, 5, 6, 7, 8 };
	
	int randomPick = rand() % choicePool.size();
	pieceType = choicePool.at(randomPick);
	choicePool.erase(choicePool.begin() + randomPick);
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
		tilemap[tile.at(0)][tile.at(1)] = this->pieceType;
	}
}

void Piece::movedown(int(&tilemap)[10][20]) {

		for (std::vector<int> tile : Occupying) {
			const int x = tile.at(0);
			const int y = tile.at(1);

			if (y + 1 >= 20 || ((tilemap[x][y + 1] != 1 && tilemap[x][y + 1] != 9) && !(std::find(Occupying.begin(), Occupying.end(), std::vector<int> {x, y + 1}) != Occupying.end()))) {//touches floor || (not empty tile && not user piece)
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

		if ((x + side > 10 && x + side < 0) || ((tilemap[x + side][y] != 1 && tilemap[x][y + side] != 9) && !(std::find(Occupying.begin(), Occupying.end(), std::vector<int> {x + side, y}) != Occupying.end()))) {//touches wall || (touches not empty tile && touches not user piece)
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

			if (y + 1 >= 20 || ((tilemap[x][y + 1] != 1 && tilemap[x][y + 1] != 9) && !(std::find(Occupying.begin(), Occupying.end(), std::vector<int> {x, y + 1}) != Occupying.end()))) {//touches floor || (not empty tile && not user piece)
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

int Piece::rotate(int(&tilemap)[10][20], int CW_CCW) {
	std::vector<std::vector<int>> newOrientation = Occupying;
	int tilenum = 0, CCW = 0;

	if (CW_CCW == -1 && orientation == 1) { CCW = 3; }//for "looping around" the rotation matrixes
	else if (CW_CCW == -1) { CCW = -1; }

	for(int i = 0; i < 4; i++){ //for each tile the piece occupies
		int x = newOrientation.at(i).at(0) += (operations[pieceType - 2][orientation - 1 + CCW][tilenum][0])*CW_CCW;
		int y = newOrientation.at(i).at(1) += (operations[pieceType - 2][orientation - 1 + CCW][tilenum][1])*CW_CCW;


		//need to check you dont hit an already placed piece
		if(tilemap[x][y] != 1 && tilemap[x][y] != 9)
		{
			for (int k = 0; k < 4; k++)
			{
				if (newOrientation.at(i) == Occupying.at(k))
				{
					break;
				}
				if (k == 3) 
				{
					std::cout << "bad\n";
					return 0;
				}
			}
		}
		if (newOrientation.at(i).at(0) >= 10 || newOrientation.at(i).at(0) < 0 //check bounds
		||  newOrientation.at(i).at(1) >= 20 || newOrientation.at(i).at(1) < 0) 
		{
			std::cout << "bad\n"; 
			return 0;
		}
		tilenum++;
	}
	//remove old piece location & then move to new location
		for (std::vector<int> tile : Occupying) {
			tilemap[tile.at(0)][tile.at(1)] = 1;
		}
		if (orientation == 4 && CW_CCW == 1) { orientation = 1; }
		else if (orientation == 1 && CW_CCW == -1) { orientation = 4; }
		else { orientation += CW_CCW; }
		
	Occupying = newOrientation;
	manifest(tilemap);
	return 1;
}

void Piece::updateShadow(int(&tilemap)[10][20])
{
	for (std::vector<int> tile : shadowOccupying) {
		tilemap[tile.at(0)][tile.at(1)] = 1;
	}
	this->shadowOccupying = this->Occupying;

	for (int y = 0; y < 20; y++) {
		for (std::vector<int> tile : shadowOccupying) {
			const int x = tile.at(0);
			const int y = tile.at(1);

			if (tilemap[x][y + 1] != 9 && (y + 1 >= 20 || ((tilemap[x][y + 1] != 1 && tilemap[x][y + 1] != 9) && !(std::find(shadowOccupying.begin(), shadowOccupying.end(), std::vector<int> {x, y + 1}) != shadowOccupying.end())))) {//touches floor || (not empty tile && not user piece)
				for (std::vector<int> tile : shadowOccupying) {
					tilemap[tile.at(0)][tile.at(1)] = 9;
				}
				return;
			}
		}
		{//remove old piece location & then move to new location
			for (std::vector<int> tile : shadowOccupying) {
				tilemap[tile.at(0)][tile.at(1)] = 1;
			}
			shadowOccupying.at(0).at(1) = shadowOccupying.at(0).at(1) + 1;
			shadowOccupying.at(1).at(1) = shadowOccupying.at(1).at(1) + 1;
			shadowOccupying.at(2).at(1) = shadowOccupying.at(2).at(1) + 1;
			shadowOccupying.at(3).at(1) = shadowOccupying.at(3).at(1) + 1;
		}
	}
}

