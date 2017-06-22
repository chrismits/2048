/*******************************
* COMP 11 Spring 2017
* Homework 6
* Christos-Nikolaos Mitsopoulos
* Signoff by [Laney Strange] [04/11/2017]
* Extra Credit
********************************/

#include <iostream>
using namespace std;

#ifndef BOARDEXTRA_H_
#define BOARDEXTRA_H_

//Empty Tile Character
const char empty = '_';

class Boarde
{
private:
	//Dimensions of the board
	int board_size;
	//2D array that represents the board and will be dynamically allocated
	int **board;
	//2D array that is a copy. Extra Credit
	int **copy;

public:
	//Class Constructor, initializes board_size and board array
	Boarde();
	//Class Destructor that deallocates 2D array
	~Boarde();

	//Set board size
	void set_board_size();
	//Function to retrieve board size. Returns board size.
	int get_board_size();

	//Dynamically allocates 2D array
	void allocate();
	//Fills array with starting tiles
	void fill();
	//Duplicate array for undo
	void duplicate();
	//Undo. Extra Credit
	void undo();
	//Sets up game. That is pulls together allocation, board size and fill
	void setup();
	//Restarts game. Extra Credit
	void restart();
	//Introduces new tile after every move, taking into account the respected
	//probabilities for 2 and 4
	void new_tile();
	//Prints Board and shows empty elements as 'X'. It also adjusts spacing
	void print();

	//Moves board elements up. Returns int that shows if movement was made
	int up();
	//Sums elements upward. Returns sum of merged tiles.
	int sum_up();

	//Moves board elements down. Returns int that shows if movement was made 
	int down();
	//Sums elements downward. Returns sum of merged tiles.
	int sum_down();
	//Moves board elements left. Returns int that shows if movement was made
	int left();
	//Sums elements leftward. Returns sum of merged tiles.
	int sum_left();
	//Moves board elements right. Returns int that shows if movement was made 
	int right();
	//Sums elements rightward. Returns sum of merged tiles.
	int sum_right();

	//Checks if all tiles are filled and no possible mergers exist.
	//Returns: Boolean
	bool game_over();
};

#endif
