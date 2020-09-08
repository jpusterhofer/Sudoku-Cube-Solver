This program generates a model of a sudoku cube. For 3 <= k <= 20, the program will apply k random rotations to the cube, print the randomized cube, run the A* algorithm to solve it, then print the solution path between the cube's randomized and solved states. The program will repeat this process 5 times for every k. The program will then calculate and print the average number of nodes generated while performing A* based on the distance between the cube's randomized and solved states.

A* uses a priority queue that stores objects of the Node class. The top element of the priority queue contains a Node that has the smallest h value of the Nodes that have the smallest f value.

The Node class contains a SudokuCube object, integers h and g, and a pointer to the Node's parent Node. Node also implements the function that calculates the sudoku cube's heuristic value.

The SudokuCube class contains 6 3x3 arrays of Tile objects, each of which represents one tile on each face on the cube. SudokuCube implements functions to rotate the cube's faces, randomize the cube by k rotations, and print a text represention of the cube's current state.

The Tile class contains the Tile's number, the number's orientation, the Tile's location on the cube, whether it's a corner piece, and its unique ID. Tile implements functions to change a Tile's number, orientation, and ID without changing its location, check if the Tile is equal to another Tile, and rotate the Tile's orientation.

The heuristic assumes there is only one solved state and uses the fact that each cubie is unique. After the cube is randomized, the heuristic assigns a unique ID to each tile. Then, it sums the minimum number of rotations it would take each tile to reach its location in the solved state, divides by 20, and rounds up. The heuristic divides by 20 because 20 tiles change location on each rotation, and it rounds up because the summation could provide a number less than 20 but greater than 0. Rounding down would incorrectly state that the cube is solved.

Compile: Run g++ *.cpp
Run: Run ./a.out [-p] k
-p prints the solution path of each solved cube
k is the number of rotations to apply to each cube. Excluding a k value will run the program for every 3 <= k <= 20.

I learned about the deque data structure. By default, the c++ priority queue is built on top of a vector, which slowed down my program every time the vector filled up and copied all of the data into another, larger vector. On the other hand, a deque doesn't need all of its elements to be in contiguous locations, so it worked better for what my program was doing.