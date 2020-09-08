#include "Node.h"

//Constructors
Node::Node()
{

}

Node::Node(SudokuCube &cube)
{
	this->cube = cube;
	h = 0;
	g = 0;
	parent = NULL;
}

Node::Node(Node* parentNode)
{
	this->cube = parentNode->cube;
	h = 0;
	g = parentNode->g + 1;
	parent = parentNode;
}

//Get functions
int Node::getH() const
{
	return h;
}

int Node::getG() const
{
	return g;
}

Node* Node::getParent() const
{
	return parent;
}

SudokuCube* Node::getCube()
{
	return &cube;
}

//Copy a Node for when one gets popped off the priority queue
void Node::copyNode(const Node* node)
{
	cube = node->cube;
	h = node->h;
	g = node->g;
	parent = node->parent;
}

//Overload > operator for the priority queue
bool operator>(const Node &node1, const Node &node2)
{
	//Compare f values
	int f1 = node1.h + node1.g;
	int f2 = node2.h + node2.g;
	if (f1 > f2)
	{
		return true;
	}

	//If f values are equal, compare h
	else if (f1 == f2)
	{
		return (node1.h > node2.h);
	}
	return false;
}

//Calculate the heuristic value
void Node::calcH(SudokuCube &solvedCube)
{
	Tile currTile;
	Tile solvedTile;
	MoveFinder finder;
	double tempH = 0;

	//For every tile, find the min number of moves needed to reach its solved location
	for (int ID = 0; ID < 54; ID++)
	{
		currTile = cube.hash(ID);
		solvedTile = solvedCube.hash(ID);
		finder = MoveFinder(currTile, solvedTile);
		tempH += finder.getMoves();
	}
	h = ceil(tempH / 20); //20 tiles move every rotation. Divide by 20 and round up to get number of rotations
}