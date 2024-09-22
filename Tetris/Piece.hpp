#ifndef PIECE_HPP
#define PIECE_HPP

#include <math.h>
#include "SDL.h"
#include <iostream>
#include <vector>
#include <algorithm>


class Piece {
public:
	Piece();
	void init(int(&tilemap)[10][20]);
	void movedown(int(&tilemap)[10][20]);
	void moveside(int(&tilemap)[10][20], int side);

	void manifest(int(&tilemap)[10][20]);
	void checkclear(int(&tilemap)[10][20]);
	void instadrop(int(&tilemap)[10][20]);
	void rotate(int(&tilemap)[10][20]);


private:

	std::vector<std::vector<int>> Occupying;
	int pieceType;
	int orientation;

	//operations[piecetype][orientation][tile][tileoperation]      
	int operations[7][4][4][2] = {
		/////////////1/////////2/////////3/////////4//////////////////////////////S[0]
			   {{{-1, -1}, { 0,  0}, { 1, -1}, { 2,  0}},  //o1->o2 done
				{{-1,  2}, { 0,  1}, {-1,  0}, { 0, -1}},  //o2->o3 done 
				{{ 2,  0}, { 1, -1}, { 0,  0}, {-1, -1}},  //o3->o4 done
				{{ 0, -1}, {-1,  0}, { 0,  1}, {-1,  2}}},//o4->o1 done
		/////////////1/////////2/////////3/////////4//////////////////////////////I[1]
			   {{{ 1, -1}, { 0,  0}, {-1,  1}, {-2,  2}},  //o1->o2 done
				{{ 2,  1}, { 1,  0}, { 0, -1}, {-1, -2}},  //o2->o3 done
				{{-1,  2}, { 0,  1}, { 1,  0}, { 2, -1}},  //o3->o4 done
				{{-2, -2}, {-1, -1}, { 0,  0}, { 1,  1}} },//o4->o1 done
		/////////////1/////////2/////////3/////////4//////////////////////////////O[2]
			   {{{ 0, -0}, { 0,  0}, {-0,  0}, { 0,  0}},  //o1->o2 done
				{{ 0,  0}, { 0,  0}, { 0,  0}, {-0, -0}},  //o2->o3 done
				{{-0,  0}, { 0,  0}, { 0,  0}, { 0, -0}},  //o3->o4 done
				{{-0, -0}, {-0, -0}, { 0,  0}, { 0,  0}} },//o4->o1 done
		/////////////1/////////2/////////3/////////4//////////////////////////////L[3]
			   {{{ 0, -2}, {-1, -1}, {-2,  0}, {-1,  1}},  //o1->o2 done
				{{ 2,  0}, { 1, -1}, { 0, -2}, {-1, -1}},  //o2->o3 done
				{{ 0,  2}, { 1,  1}, { 2,  0}, { 1, -1}},  //o3->o4 done 
				{{-2,  0}, {-1,  1}, { 0,  2}, { 1,  1}}}, //o4->o1 done
		/////////////1/////////2/////////3/////////4//////////////////////////////T[4]
			   {{{ 1,  1}, {-0, -0}, {-1,  1}, { 1, -1}},  //o1->o2 done
				{{-1,  1}, { 0, -0}, {-1, -1}, { 1,  1}},  //o2->o3 done
				{{-1, -1}, { 0,  0}, { 1, -1}, {-1,  1}},  //o3->o4 done
				{{ 1, -1}, {-0,  0}, { 1,  1}, {-1, -1}}}, //o4->o1 done
		/////////////1/////////2/////////3/////////4//////////////////////////////Z[5]
			   {{{ 2,  0}, { 1,  1}, { 0, -0}, {-1,  1}},  //o1->o2 done
				{{ 0,  2}, {-1,  1}, {-0,  0}, {-1, -1}},  //o2->o3 done
				{{-1,  0}, { 0, -1}, { 1,  0}, { 2, -1}},  //o3->o4 done
				{{-1, -2}, {-0, -1}, {-1,  0}, {-2,  1}}}, //o4->o1 done
		/////////////1/////////2/////////3/////////4//////////////////////////////J[6]
			   {{{ 1, -1}, {-0, -2}, {-1, -1}, {-2,  0}},  //o1->o2 done
				{{ 1,  1}, { 2, -0}, { 1, -1}, {-0, -2}},  //o2->o3 done
				{{-1,  1}, { 0,  2}, { 1,  1}, { 2, -0}},  //o3->o4 done 
				{{-1, -1}, {-2,  0}, {-1,  1}, { 0,  2}}}, //o4->o1 done
	};
	/* S  o1          o2		  o3         o4
		 0 0 0 0    0 1 0 0	   0 0 0 0    0 4 0 0
   o4 -> 0 2 1 0 -> 0 2 3 0 -> 0 3 4 0 -> 0 3 2 0 -> o1
		 4 3 0 0    0 0 4 0	   1 2 0 0    0 0 1 0
		 0 0 0 0    0 0 0 0	   0 0 0 0    0 0 0 0

// I		o1          o2		  o3         o4
		 0 0 0 0    0 1 0 0	   0 0 0 0    0 0 4 0
   o4 -> 1 2 3 4 -> 0 2 0 0 -> 4 3 2 1 -> 0 0 3 0 -> o1
		 0 0 0 0    0 3 0 0	   0 0 0 0    0 0 2 0
		 0 0 0 0    0 4 0 0	   0 0 0 0    0 0 1 0

// O		o1          o2		  o3         o4
		 0 0 0 0    0 0 0 0	   0 0 0 0    0 0 0 0
   o4 -> 0 2 3 0 -> 0 1 2 0 -> 0 4 1 0 -> 0 3 4 0 -> o1
		 0 1 4 0    0 4 3 0	   0 3 2 0    0 2 1 0
		 0 0 0 0    0 0 0 0	   0 0 0 0    0 0 0 0
// L
			o1          o2		  o3         o4
		 0 0 0 0    1 0 0 0	   3 2 1 0    0 4 3 0
   o4 -> 0 0 4 0 -> 2 0 0 0 -> 4 0 0 0 -> 0 0 2 0 -> o1
		 1 2 3 0    3 4 0 0	   0 0 0 0    0 0 1 0
		 0 0 0 0    0 0 0 0	   0 0 0 0    0 0 0 0

// T
			o1          o2		  o3         o4
		 0 0 0 0    0 0 0 0	   0 0 0 0    0 0 0 0
   o4 -> 0 1 0 0 -> 0 4 0 0 -> 0 0 0 0 -> 0 3 0 0 -> o1
		 4 2 3 0    0 2 1 0	   3 2 4 0    1 2 0 0
		 0 0 0 0    0 3 0 0	   0 1 0 0    0 4 0 0

// Z		o1          o2		  o3         o4
		 0 0 0 0    0 0 0 0	   0 0 0 0    0 0 0 0
   o4 -> 1 2 0 0 -> 0 0 1 0 -> 0 0 0 0 -> 0 0 4 0 -> o1
		 0 3 4 0    0 3 2 0	   4 3 0 0    0 2 3 0
		 0 0 0 0    0 4 0 0	   0 2 1 0    0 1 0 0

// J
			o1          o2		  o3         o4
		 0 0 0 0    2 1 0 0	   4 3 2 0    0 0 4 0
   o4 -> 1 0 0 0 -> 3 0 0 0 -> 0 0 1 0 -> 0 0 3 0 -> o1
		 2 3 4 0    4 0 0 0	   0 0 0 0    0 1 2 0
		 0 0 0 0    0 0 0 0	   0 0 0 0    0 0 0 0
	*/
};






#endif // !PIECE_HPP
