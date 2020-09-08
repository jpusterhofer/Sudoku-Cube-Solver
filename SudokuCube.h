#pragma once
#include "Tile.h"
#include <string>
using namespace std;

class SudokuCube
{
public:
	SudokuCube();
	void randomize(int n);
	void print();
	Tile hash(int ID);

	void rotateFrontCW();
	void rotateTopCW();
	void rotateBottomCW();
	void rotateBackCW();
	void rotateLeftCW();
	void rotateRightCW();

	void rotateFrontCCW();
	void rotateTopCCW();
	void rotateBottomCCW();
	void rotateBackCCW();
	void rotateLeftCCW();
	void rotateRightCCW();

private:
	Tile front[3][3];
	Tile top[3][3];
	Tile bottom[3][3];
	Tile back[3][3];
	Tile left[3][3];
	Tile right[3][3];
	Tile* hashTbl[54];

	void IDTiles();
	void rotateFaceCW(Tile face[3][3]);
	void rotateFaceCCW(Tile face[3][3]);
};
