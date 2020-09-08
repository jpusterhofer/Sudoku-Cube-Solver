#include <iostream>
#include <time.h>
#include "Cubie.h"
#include "SudokuCube.h"
using namespace std;

//Set initial state for the cube
SudokuCube::SudokuCube()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			front[i][j] = Tile("front", i, j, '^');
		}
	}
	front[0][0].setNum(1);
	front[0][1].setNum(5);
	front[0][2].setNum(2);
	front[1][0].setNum(4);
	front[1][1].setNum(6);
	front[1][2].setNum(3);
	front[2][0].setNum(7);
	front[2][1].setNum(8);
	front[2][2].setNum(9);
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			top[i][j] = Tile("top", i, j, '^');
		}
	}
	top[0][0].setNum(9);
	top[0][1].setNum(7);
	top[0][2].setNum(1);
	top[1][0].setNum(2);
	top[1][1].setNum(4);
	top[1][2].setNum(8);
	top[2][0].setNum(5);
	top[2][1].setNum(3);
	top[2][2].setNum(6);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			bottom[i][j] = Tile("bottom", i, j, 'v');
		}
	}
	bottom[0][0].setNum(5);
	bottom[0][1].setNum(9);
	bottom[0][2].setNum(6);
	bottom[1][0].setNum(3);
	bottom[1][1].setNum(7);
	bottom[1][2].setNum(8);
	bottom[2][0].setNum(2);
	bottom[2][1].setNum(4);
	bottom[2][2].setNum(1);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			back[i][j] = Tile("back", i, j, 'v');
		}
	}
	back[0][0].setNum(8);
	back[0][1].setNum(2);
	back[0][2].setNum(9);
	back[1][0].setNum(1);
	back[1][1].setNum(5);
	back[1][2].setNum(7);
	back[2][0].setNum(6);
	back[2][1].setNum(3);
	back[2][2].setNum(4);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			left[i][j] = Tile("left", i, j, '^');
		}
	}
	left[0][0].setNum(3);
	left[0][1].setNum(8);
	left[0][2].setNum(7);
	left[1][0].setNum(2);
	left[1][1].setNum(1);
	left[1][2].setNum(9);
	left[2][0].setNum(5);
	left[2][1].setNum(6);
	left[2][2].setNum(4);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			right[i][j] = Tile("right", i, j, '>');
		}
	}
	right[0][0].setNum(8);
	right[0][1].setNum(6);
	right[0][2].setNum(3);
	right[1][0].setNum(2);
	right[1][1].setNum(1);
	right[1][2].setNum(9);
	right[2][0].setNum(4);
	right[2][1].setNum(5);
	right[2][2].setNum(7);

	for (int i = 0; i < 52; i++)
	{
		hashTbl[i] = NULL;
	}
}

//Randomize the sudoku cube by n rotations
void SudokuCube::randomize(int n)
{
	int randNum;
	srand(time(NULL));

	while (n > 0)
	{
		randNum = rand() % 6; //Generate random numbers between 0 and 5
		switch (randNum)
		{
			case 0:
				rotateFrontCW();
				break;
			case 1:
				rotateTopCW();
				break;
			case 2:
				rotateBottomCW();
				break;
			case 3:
				rotateBackCW();
				break;
			case 4:
				rotateLeftCW();
				break;
			case 5:
				rotateRightCW();
				break;
		}
		n--;
	}
	IDTiles();
}

//Print an ASCII representation of the cube's current state
void SudokuCube::print()
{
	cout << "               --- --- --- " << endl;
	cout << "              | " << top[0][0].getNum() << top[0][0].getDir() << "| " << top[0][1].getNum() << top[0][1].getDir() << "| " << top[0][2].getNum() << top[0][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;
	cout << "              | " << top[1][0].getNum() << top[1][0].getDir() << "| " << top[1][1].getNum() << top[1][1].getDir() << "| " << top[1][2].getNum() << top[1][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;
	cout << "              | " << top[2][0].getNum() << top[2][0].getDir() << "| " << top[2][1].getNum() << top[2][1].getDir() << "| " << top[2][2].getNum() << top[2][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;

	cout << " --- --- --- ";
	cout << "  --- --- --- ";
	cout << "  --- --- --- " << endl;
	cout << "| " << left[0][0].getNum() << left[0][0].getDir() << "| " << left[0][1].getNum() << left[0][1].getDir() << "| " << left[0][2].getNum() << left[0][2].getDir() << "| ";
	cout << "| " << front[0][0].getNum() << front[0][0].getDir() << "| " << front[0][1].getNum() << front[0][1].getDir() << "| " << front[0][2].getNum() << front[0][2].getDir() << "| ";
	cout << "| " << right[0][0].getNum() << right[0][0].getDir() << "| " << right[0][1].getNum() << right[0][1].getDir() << "| " << right[0][2].getNum() << right[0][2].getDir() << "| " << endl;
	cout << " --- --- --- ";
	cout << "  --- --- --- ";
	cout << "  --- --- --- " << endl;
	cout << "| " << left[1][0].getNum() << left[1][0].getDir() << "| " << left[1][1].getNum() << left[1][1].getDir() << "| " << left[1][2].getNum() << left[1][2].getDir() << "| ";
	cout << "| " << front[1][0].getNum() << front[1][0].getDir() << "| " << front[1][1].getNum() << front[1][1].getDir() << "| " << front[1][2].getNum() << front[1][2].getDir() << "| ";
	cout << "| " << right[1][0].getNum() << right[1][0].getDir() << "| " << right[1][1].getNum() << right[1][1].getDir() << "| " << right[1][2].getNum() << right[1][2].getDir() << "| " << endl;
	cout << " --- --- --- ";
	cout << "  --- --- --- ";
	cout << "  --- --- --- " << endl;
	cout << "| " << left[2][0].getNum() << left[2][0].getDir() << "| " << left[2][1].getNum() << left[2][1].getDir() << "| " << left[2][2].getNum() << left[2][2].getDir() << "| ";
	cout << "| " << front[2][0].getNum() << front[2][0].getDir() << "| " << front[2][1].getNum() << front[2][1].getDir() << "| " << front[2][2].getNum() << front[2][2].getDir() << "| ";
	cout << "| " << right[2][0].getNum() << right[2][0].getDir() << "| " << right[2][1].getNum() << right[2][1].getDir() << "| " << right[2][2].getNum() << right[2][2].getDir() << "| " << endl;
	cout << " --- --- --- ";
	cout << "  --- --- --- ";
	cout << "  --- --- --- " << endl;

	cout << "               --- --- --- " << endl;
	cout << "              | " << bottom[0][0].getNum() << bottom[0][0].getDir() << "| " << bottom[0][1].getNum() << bottom[0][1].getDir() << "| " << bottom[0][2].getNum() << bottom[0][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;
	cout << "              | " << bottom[1][0].getNum() << bottom[1][0].getDir() << "| " << bottom[1][1].getNum() << bottom[1][1].getDir() << "| " << bottom[1][2].getNum() << bottom[1][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;
	cout << "              | " << bottom[2][0].getNum() << bottom[2][0].getDir() << "| " << bottom[2][1].getNum() << bottom[2][1].getDir() << "| " << bottom[2][2].getNum() << bottom[2][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;

	cout << "               --- --- --- " << endl;
	cout << "              | " << back[0][0].getNum() << back[0][0].getDir() << "| " << back[0][1].getNum() << back[0][1].getDir() << "| " << back[0][2].getNum() << back[0][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;
	cout << "              | " << back[1][0].getNum() << back[1][0].getDir() << "| " << back[1][1].getNum() << back[1][1].getDir() << "| " << back[1][2].getNum() << back[1][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;
	cout << "              | " << back[2][0].getNum() << back[2][0].getDir() << "| " << back[2][1].getNum() << back[2][1].getDir() << "| " << back[2][2].getNum() << back[2][2].getDir() << "| " << endl;
	cout << "               --- --- --- " << endl;
	cout << endl;
}

//Set a unique ID to each tile
void SudokuCube::IDTiles()
{
	Cubie cubies[20];

	//Center tiles never move
	front[1][1].setID(4);
	top[1][1].setID(13);
	bottom[1][1].setID(22);
	back[1][1].setID(31);
	left[1][1].setID(40);
	right[1][1].setID(49);

	//Group the tiles together based on their cubie
	cubies[0] = Cubie(&front[0][0], &top[2][0], &left[0][2]);
	cubies[1] = Cubie(&front[0][2], &top[2][2], &right[0][0]);
	cubies[2] = Cubie(&front[2][2], &bottom[0][2], &right[2][0]);
	cubies[3] = Cubie(&front[2][0], &bottom[0][0], &left[2][2]);
	cubies[4] = Cubie(&back[0][0], &bottom[2][0], &left[2][0]);
	cubies[5] = Cubie(&back[0][2], &bottom[2][2], &right[2][2]);
	cubies[6] = Cubie(&back[2][2], &top[0][2], &right[0][2]);
	cubies[7] = Cubie(&back[2][0], &top[0][0], &left[0][0]);

	cubies[8] = Cubie(&front[0][1], &top[2][1]);
	cubies[9] = Cubie(&front[1][2], &right[1][0]);
	cubies[10] = Cubie(&front[2][1], &bottom[0][1]);
	cubies[11] = Cubie(&front[1][0], &left[1][2]);
	cubies[12] = Cubie(&back[0][1], &bottom[2][1]);
	cubies[13] = Cubie(&back[1][2], &right[1][2]);
	cubies[14] = Cubie(&back[2][1], &top[0][1]);
	cubies[15] = Cubie(&back[1][0], &left[1][0]);
	cubies[16] = Cubie(&top[1][0], &left[0][1]);
	cubies[17] = Cubie(&top[1][2], &right[0][1]);
	cubies[18] = Cubie(&bottom[1][0], &left[2][1]);
	cubies[19] = Cubie(&bottom[1][2], &right[2][1]);

	//ID the corner pieces
	for (int i = 0; i < 8; i++)
	{
		if (cubies[i].containsNums(1, 5, 7))
		{
			cubies[i].find(1)->setID(0);
			cubies[i].find(5)->setID(15);
			cubies[i].find(7)->setID(38);
		}
		else if (cubies[i].containsNums(2, 6, 8))
		{
			cubies[i].find(2)->setID(2);
			cubies[i].find(6)->setID(17);
			cubies[i].find(8)->setID(45);
		}
		else if (cubies[i].containsNums(7, 4, 5))
		{
			cubies[i].find(7)->setID(6);
			cubies[i].find(4)->setID(44);
			cubies[i].find(5)->setID(18);
		}
		else if (cubies[i].containsNums(9, 6, 4))
		{
			cubies[i].find(9)->setID(8);
			cubies[i].find(6)->setID(20);
			cubies[i].find(4)->setID(51);
		}
		else if (cubies[i].containsNums(8, 2, 5))
		{
			cubies[i].find(8)->setID(27);
			cubies[i].find(2)->setID(24);
			cubies[i].find(5)->setID(42);
		}
		else if (cubies[i].containsNums(9, 1, 7))
		{
			cubies[i].find(9)->setID(29);
			cubies[i].find(1)->setID(26);
			cubies[i].find(7)->setID(53);
		}
		else if (cubies[i].containsNums(4, 1, 3))
		{
			cubies[i].find(4)->setID(35);
			cubies[i].find(1)->setID(11);
			cubies[i].find(3)->setID(47);
		}
		else if (cubies[i].containsNums(6, 9, 3))
		{
			cubies[i].find(6)->setID(33);
			cubies[i].find(9)->setID(9);
			cubies[i].find(3)->setID(36);
		}
	}

	//ID the edge pieces
	for (int i = 8; i < 20; i++)
	{
		if (cubies[i].containsNums(5, 3))
		{
			cubies[i].find(5)->setID(1);
			cubies[i].find(3)->setID(16);
		}
		else if (cubies[i].containsNums(3, 2))
		{
			cubies[i].find(3)->setID(5);
			cubies[i].find(2)->setID(48);
		}
		else if (cubies[i].containsNums(8, 9))
		{
			cubies[i].find(8)->setID(7);
			cubies[i].find(9)->setID(19);
		}
		else if (cubies[i].containsNums(4, 9))
		{
			cubies[i].find(4)->setID(3);
			cubies[i].find(9)->setID(41);
		}
		else if (cubies[i].containsNums(2, 4))
		{
			cubies[i].find(2)->setID(28);
			cubies[i].find(4)->setID(25);
		}
		else if (cubies[i].containsNums(7, 9))
		{
			cubies[i].find(7)->setID(32);
			cubies[i].find(9)->setID(50);
		}
		else if (cubies[i].containsNums(3, 7))
		{
			cubies[i].find(3)->setID(34);
			cubies[i].find(7)->setID(10);
		}
		else if (cubies[i].containsNums(1, 2))
		{
			cubies[i].find(1)->setID(30);
			cubies[i].find(2)->setID(39);
		}
		else if (cubies[i].containsNums(3, 6))
		{
			cubies[i].find(3)->setID(21);
			cubies[i].find(6)->setID(43);
		}
		else if (cubies[i].containsNums(8, 5))
		{
			cubies[i].find(8)->setID(23);
			cubies[i].find(5)->setID(52);
		}
		else if (cubies[i].containsNums(2, 8))
		{
			cubies[i].find(2)->setID(12);
			cubies[i].find(8)->setID(37);
		}
		else if (cubies[i].containsNums(8, 6))
		{
			cubies[i].find(8)->setID(14);
			cubies[i].find(6)->setID(46);
		}
	}

	//Enter the tiles into a hash table for fast search
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			hashTbl[front[i][j].getID()] = &front[i][j];
			hashTbl[top[i][j].getID()] = &top[i][j];
			hashTbl[bottom[i][j].getID()] = &bottom[i][j];
			hashTbl[back[i][j].getID()] = &back[i][j];
			hashTbl[left[i][j].getID()] = &left[i][j];
			hashTbl[right[i][j].getID()] = &right[i][j];
		}
	}

}

//Rotate the tiles on one particular face clockwise
void SudokuCube::rotateFaceCW(Tile face[3][3])
{
	//Copy the face
	Tile temp[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = face[i][j];
		}
	}

	//Rotate the numbers and orientations
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			face[i][j].changeTile(temp[2 - j][i]);
			face[i][j].rotateTileCW();
			hashTbl[face[i][j].getID()] = &face[i][j];
		}
	}
}

//Rotate the tiles on one particular face counterclockwise
void SudokuCube::rotateFaceCCW(Tile face[3][3])
{
	//Copy the face
	Tile temp[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[i][j] = face[i][j];
		}
	}

	//Rotate the numbers and orientations
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			face[i][j].changeTile(temp[j][2 - i]);
			face[i][j].rotateTileCCW();
			hashTbl[face[i][j].getID()] = &face[i][j];
		}
	}
}

//Rotate the front face clockwise
void SudokuCube::rotateFrontCW()
{
	rotateFaceCW(front);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = top[2][i];
		top[2][i].changeTile(left[2 - i][2]);
		top[2][i].rotateTileCW();
		hashTbl[top[2][i].getID()] = &top[2][i];

		left[2 - i][2].changeTile(bottom[0][2 - i]);
		left[2 - i][2].rotateTileCW();
		hashTbl[left[2 - i][2].getID()] = &left[2 - i][2];

		bottom[0][2 - i].changeTile(right[i][0]);
		bottom[0][2 - i].rotateTileCW();
		hashTbl[bottom[0][2 - i].getID()] = &bottom[0][2 - i];

		right[i][0].changeTile(temp);
		right[i][0].rotateTileCW();
		hashTbl[right[i][0].getID()] = &right[i][0];
	}
}

//Rotate the top face clockwise
void SudokuCube::rotateTopCW()
{
	rotateFaceCW(top);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = front[0][i];
		front[0][i].changeTile(right[0][i]);
		hashTbl[front[0][i].getID()] = &front[0][i];

		right[0][i].changeTile(back[2][2 - i]);
		right[0][i].flipTile();
		hashTbl[right[0][i].getID()] = &right[0][i];

		back[2][2 - i].changeTile(left[0][i]);
		back[2][2 - i].flipTile();
		hashTbl[back[2][2 - i].getID()] = &back[2][2 - i];

		left[0][i].changeTile(temp);
		hashTbl[left[0][i].getID()] = &left[0][i];
	}
}

//Rotate the bottom face clockwise
void SudokuCube::rotateBottomCW()
{
	rotateFaceCW(bottom);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = front[2][i];
		front[2][i].changeTile(left[2][i]);
		hashTbl[front[2][i].getID()] = &front[2][i];

		left[2][i].changeTile(back[0][2 - i]);
		left[2][i].flipTile();
		hashTbl[left[2][i].getID()] = &left[2][i];

		back[0][2 - i].changeTile(right[2][i]);
		back[0][2 - i].flipTile();
		hashTbl[back[0][2 - i].getID()] = &back[0][2 - i];

		right[2][i].changeTile(temp);
		hashTbl[right[2][i].getID()] = &right[2][i];
	}
}

//Rotate the back face clockwise
void SudokuCube::rotateBackCW()
{
	rotateFaceCW(back);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = right[i][2];
		right[i][2].changeTile(bottom[2][2 - i]);
		right[i][2].rotateTileCCW();
		hashTbl[right[i][2].getID()] = &right[i][2];

		bottom[2][2 - i].changeTile(left[2 - i][0]);
		bottom[2][2 - i].rotateTileCCW();
		hashTbl[bottom[2][2 - i].getID()] = &bottom[2][2 - i];

		left[2 - i][0].changeTile(top[0][i]);
		left[2 - i][0].rotateTileCCW();
		hashTbl[left[2 - i][0].getID()] = &left[2 - i][0];

		top[0][i].changeTile(temp);
		top[0][i].rotateTileCCW();
		hashTbl[top[0][i].getID()] = &top[0][i];
	}
}

//Rotate the left face clockwise
void SudokuCube::rotateLeftCW()
{
	rotateFaceCW(left);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = front[i][0];
		front[i][0].changeTile(top[i][0]);
		hashTbl[front[i][0].getID()] = &front[i][0];

		top[i][0].changeTile(back[i][0]);
		hashTbl[top[i][0].getID()] = &top[i][0];

		back[i][0].changeTile(bottom[i][0]);
		hashTbl[back[i][0].getID()] = &back[i][0];

		bottom[i][0].changeTile(temp);
		hashTbl[bottom[i][0].getID()] = &bottom[i][0];
	}
}

//Rotate the right face clockwise
void SudokuCube::rotateRightCW()
{
	rotateFaceCW(right);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = front[i][2];
		front[i][2].changeTile(bottom[i][2]);
		hashTbl[front[i][2].getID()] = &front[i][2];

		bottom[i][2].changeTile(back[i][2]);
		hashTbl[bottom[i][2].getID()] = &bottom[i][2];

		back[i][2].changeTile(top[i][2]);
		hashTbl[back[i][2].getID()] = &back[i][2];

		top[i][2].changeTile(temp);
		hashTbl[top[i][2].getID()] = &top[i][2];
	}
}

//Rotate the front face counterclockwise
void SudokuCube::rotateFrontCCW()
{
	rotateFaceCCW(front);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = top[2][i];
		top[2][i].changeTile(right[i][0]);
		top[2][i].rotateTileCCW();
		hashTbl[top[2][i].getID()] = &top[2][i];

		right[i][0].changeTile(bottom[0][2 - i]);
		right[i][0].rotateTileCCW();
		hashTbl[right[i][0].getID()] = &right[i][0];

		bottom[0][2 - i].changeTile(left[2 - i][2]);
		bottom[0][2 - i].rotateTileCCW();
		hashTbl[bottom[0][2 - i].getID()] = &bottom[0][2 - i];

		left[2 - i][2].changeTile(temp);
		left[2 - i][2].rotateTileCCW();
		hashTbl[left[2 - i][2].getID()] = &left[2 - i][2];
	}
}

//Rotate the top face counterclockwise
void SudokuCube::rotateTopCCW()
{
	rotateFaceCCW(top);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = front[0][i];
		front[0][i].changeTile(left[0][i]);
		hashTbl[front[0][i].getID()] = &front[0][i];

		left[0][i].changeTile(back[2][2 - i]);
		left[0][i].flipTile();
		hashTbl[left[0][i].getID()] = &left[0][i];

		back[2][2 - i].changeTile(right[0][i]);
		back[2][2 - i].flipTile();
		hashTbl[back[2][2 - i].getID()] = &back[2][2 - i];

		right[0][i].changeTile(temp);
		hashTbl[right[0][i].getID()] = &right[0][i];
	}
}

//Rotate the bottom face counterclockwise
void SudokuCube::rotateBottomCCW()
{
	rotateFaceCCW(bottom);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = front[2][i];
		front[2][i].changeTile(right[2][i]);
		hashTbl[front[2][i].getID()] = &front[2][i];

		right[2][i].changeTile(back[0][2 - i]);
		right[2][i].flipTile();
		hashTbl[right[2][i].getID()] = &right[2][i];

		back[0][2 - i].changeTile(left[2][i]);
		back[0][2 - i].flipTile();
		hashTbl[back[0][2 - i].getID()] = &back[0][2 - i];

		left[2][i].changeTile(temp);
		hashTbl[left[2][i].getID()] = &left[2][i];
	}
}

//Rotate the back face counterclockwise
void SudokuCube::rotateBackCCW()
{
	rotateFaceCCW(back);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = right[i][2];
		right[i][2].changeTile(top[0][i]);
		right[i][2].rotateTileCW();
		hashTbl[right[i][2].getID()] = &right[i][2];

		top[0][i].changeTile(left[2 - i][0]);
		top[0][i].rotateTileCW();
		hashTbl[top[0][i].getID()] = &top[0][i];

		left[2 - i][0].changeTile(bottom[2][2 - i]);
		left[2 - i][0].rotateTileCW();
		hashTbl[left[2 - i][0].getID()] = &left[2 - i][0];

		bottom[2][2 - i].changeTile(temp);
		bottom[2][2 - i].rotateTileCW();
		hashTbl[bottom[2][2 - i].getID()] = &bottom[2][2 - i];
	}
}

//Rotate the left face counterclockwise
void SudokuCube::rotateLeftCCW()
{
	rotateFaceCCW(left);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = front[i][0];
		front[i][0].changeTile(bottom[i][0]);
		hashTbl[front[i][0].getID()] = &front[i][0];

		bottom[i][0].changeTile(back[i][0]);
		hashTbl[bottom[i][0].getID()] = &bottom[i][0];

		back[i][0].changeTile(top[i][0]);
		hashTbl[back[i][0].getID()] = &back[i][0];

		top[i][0].changeTile(temp);
		hashTbl[top[i][0].getID()] = &top[i][0];
	}
}

//Rotate the right face counterclockwise
void SudokuCube::rotateRightCCW()
{
	rotateFaceCCW(right);
	Tile temp;
	for (int i = 0; i < 3; i++)
	{
		temp = front[i][2];
		front[i][2].changeTile(top[i][2]);
		hashTbl[front[i][2].getID()] = &front[i][2];

		top[i][2].changeTile(back[i][2]);
		hashTbl[top[i][2].getID()] = &top[i][2];

		back[i][2].changeTile(bottom[i][2]);
		hashTbl[back[i][2].getID()] = &back[i][2];

		bottom[i][2].changeTile(temp);
		hashTbl[bottom[i][2].getID()] = &bottom[i][2];
	}
}

Tile SudokuCube::hash(int ID)
{
	return *hashTbl[ID];
}