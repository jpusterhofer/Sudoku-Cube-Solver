#pragma once
#include "SudokuCube.h"
#include "MoveFinder.h"
#include <math.h>
class Node
{
public:
	Node();
	Node(SudokuCube &cube);
	Node(Node* parentNode);

	int getH() const;
	int getG() const;
	Node* getParent() const;
	SudokuCube* getCube();

	void copyNode(const Node* node);
	void calcH(SudokuCube &solvedCube);
	friend bool operator>(const Node &node1, const Node &node2);

private:
	SudokuCube cube;
	int h;
	int g;
	Node* parent;
};