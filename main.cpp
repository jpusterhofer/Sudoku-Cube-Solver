#include <iostream>
#include <queue>
#include <list>
#include <sstream>
#include <iomanip>
#include "Node.h"
using namespace std;

//Function prototypes
void AStar(SudokuCube &cube, double nodesExpanded[], double numCubes[], bool print);
void printSolnPath(Node* startNode);

int main(int argc, char* argv[])
{
	SudokuCube cube;
	int k = -1; //The number of rotations when the cube is randomized
	double nodesExpanded[21]; //How many nodes were expanded when running A*
	double numCubes[21]; //How many cubes had a certain distance from the solved state
	bool print = false; //Whether the solution path will be printed
	string arg; //String for parsing command line arguments

	for (int i = 0; i < 21; i++)
	{
		nodesExpanded[i] = 0;
		numCubes[i] = 0;
	}

	//Check command line arguments
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			arg = argv[i];
			//If -p is entered, print the solution path
			if (arg == "-p")
			{
				print = true;
			}

			//If user enters a number k, rotate the cube by k rotations
			else
			{
				istringstream iss(arg);
				if (!(iss >> k))
				{
					k = -1;
				}
			}
		}
	}

	cout << setprecision(16); //Print up to 16 digits for the average number of nodes expanded

    //Display the original cube
	if (print)
	{
		cout << "Solved cube" << endl;
		cube.print();
	}
	
	//If the user doesn't specify k, run for every 3 <= k <= 20
	if (k == -1)
	{
		//Run k randomizations, for 3 <= k <= 20
		for (k = 3; k <= 20; k++)
		{
			cout << "k = " << k << endl;

			//Randomize 5 cubes for every k
			for (int i = 0; i < 5; i++)
			{
				cube.randomize(k);
				
				//Run A*
				if (print)
				{
					cout << "Cube " << i + 1 << endl;
					cout << "Randomized state" << endl;
					cube.print();
					cout << "Solving... " << flush;
					AStar(cube, nodesExpanded, numCubes, print);
					cout << endl;
				}
				else
				{
					cout <<  "Cube " << i + 1 << ": Solving... " << flush;
					AStar(cube, nodesExpanded, numCubes, print);
					cout << "done" << endl;
				}
				
				cube = SudokuCube(); //Reset the cube
			}

			//Print the average number of nodes expanded
			for (int i = 0; i <= 20; i++)
			{
				if (numCubes[i] > 0)
				{
					cout << "Distance: " << i << "\tAvg. Nodes Expanded: " << nodesExpanded[i] / numCubes[i] << endl;
				}
			}

		}
	}

	//If user enters k
	else
	{
		//Run A* on 5 cubes
		for (int i = 0; i < 5; i++)
		{
			cube.randomize(k);
			
			//Run A*
			if (print)
			{
				cout << "Cube " << i + 1 << endl;
				cout << "Randomized state" << endl;
				cube.print();
				cout << "Solving... " << flush;
				AStar(cube, nodesExpanded, numCubes, print);
				cout << endl;
			}
			else
			{
				cout << "Cube " << i + 1 << ": Solving... " << flush;
				AStar(cube, nodesExpanded, numCubes, print);
				cout << "done" << endl;
			}
			cube = SudokuCube(); //Reset the cube
		}

		//Print the average number of nodes expanded
		for (int i = 0; i <= 20; i++)
		{
			if (numCubes[i] > 0)
			{
				cout << "Distance: " << i << "\tAvg. Nodes Expanded: " << nodesExpanded[i] / numCubes[i] << endl;
			}
		}
	}

	return 0;
}

//Run the A* algorithm to solve the cube
void AStar(SudokuCube &cube, double nodesExpanded[], double numCubes[], bool print)
{
	priority_queue<Node, deque<Node>, greater<Node>> q; //Priority queue for finding the Node with the lowest f val
	list<Node*> poppedNodes; //Keep track of popped Nodes to deallocate later
	Node childNode; //Make child Nodes to push onto the queue
	bool done = false; //Check if the solution was found
	int numNodes = 0; //Track how many Nodes were expanded

	//Have a solved cube for reference
	SudokuCube solvedCube;
	solvedCube.randomize(0);

	Node* currNode;
	currNode = new Node(cube);
	currNode->calcH(solvedCube); //Calculate the heuristic
	q.push(*currNode); //Push the node containing the randomized cube onto the queue
	delete currNode;

	while (!done)
	{
		//Make a copy of the top of the priority queue so it doesn't get destroyed when popped
		currNode = new Node();
		currNode->copyNode(&q.top());
		q.pop();

		//Keep track of every popped node to deallocate later
		poppedNodes.push_back(currNode);

		//If solved, done
		if (currNode->getH() == 0)
		{
			done = true;
		}
		
		//Push 6 new nodes onto queue with different cube rotations applied
		else
		{
			childNode = Node(currNode);
			childNode.getCube()->rotateFrontCCW();
			childNode.calcH(solvedCube);
			q.push(childNode);

			childNode = Node(currNode);
			childNode.getCube()->rotateTopCCW();
			childNode.calcH(solvedCube);
			q.push(childNode);

			childNode = Node(currNode);
			childNode.getCube()->rotateBottomCCW();
			childNode.calcH(solvedCube);
			q.push(childNode);

			childNode = Node(currNode);
			childNode.getCube()->rotateBackCCW();
			childNode.calcH(solvedCube);
			q.push(childNode);

			childNode = Node(currNode);
			childNode.getCube()->rotateLeftCCW();
			childNode.calcH(solvedCube);
			q.push(childNode);

			childNode = Node(currNode);
			childNode.getCube()->rotateRightCCW();
			childNode.calcH(solvedCube);
			q.push(childNode);

			numNodes += 6; //Add 6 to the number of Nodes expanded
		}
	}

	//Update data for calculating the average number of Nodes expanded
	nodesExpanded[currNode->getG()] += numNodes;
	numCubes[currNode->getG()]++;

	if (print)
	{
		printSolnPath(currNode);
	}
	
	//Deallocate nodes
	for (auto it = poppedNodes.begin(); it != poppedNodes.end(); it++)
	{
		delete *it;
	}
}

//Print the solution path
void printSolnPath(Node* startNode)
{
	list<Node*> solnPath;
	Node* currNode = startNode;

	//Add nodes to the list in reverse order
	while (currNode->getParent() != NULL)
	{
		solnPath.push_front(currNode);
		currNode = currNode->getParent();
	}

	//Print the cubes along the solution path
	cout << "done" << endl;
	for (auto it = solnPath.begin(); it != solnPath.end(); it++)
	{
		currNode = *it;
		currNode->getCube()->print();
	}
}
