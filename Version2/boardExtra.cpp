/*******************************
* COMP 11 Spring 2017
* Homework 7
* Extra Credit
* Christos-Nikolaos Mitsopoulos
********************************/

/************Extra Credit*************
* Added a restart option (press 'r')
* Added difficulty levels
* Added an undo button
*************************************/

#include <iostream>
#include "BoardExtra.h"
#include <cstdlib>
using namespace std;

//Default constructor
Boarde::Boarde()
{
	board_size = 0;
	board = NULL;
	copy = NULL;
}
//Destructor
Boarde::~Boarde()
{
	for (int i = 0; i < board_size; i++)
	{
		delete []board[i];
		delete []copy[i];
	}
	delete []board;
	delete []copy;
}
//Set board size
void Boarde::set_board_size()
{
	char level;
	do
	{
		cout << "Enter the level of difficulty: \n";
		cout << "e for easy \n";
		cout << "m for medium \n";
		cout << "h for hard \n";
		cin >> level;
	} while (level != 'e' && level != 'm' && level != 'h');
	if (level == 'e')
	{
		cout << "Easy it is! \n";
		board_size = 5;
	}
	else if (level == 'm')
	{
		cout << "Medium it is! \n";
		board_size = 4;
	}
	else
	{
		cout << "Hard it is! \n";
		board_size = 3;
	}
}

//Get board size
int Boarde::get_board_size()
{
	return board_size;
}

//Restart game
void Boarde::restart()
{
	char temp;
	cout << "Are you sure you want to restart? (y/n) \n";
	cin >> temp;

	if (temp == 'y')
	{	
		fill();
		cout << "Restarting Game.... \n\n";
	}
}

//2D array allocation
void Boarde::allocate()
{
	board = new int* [board_size];
	copy = new int* [board_size];
	for (int i = 0; i < board_size; ++i)
	{
		board[i] = new int[board_size];
		copy[i] = new int[board_size];
	}
}

//Filling array
void Boarde::fill()
{
	//Fill with zeros
	for (int i = 0; i < board_size; ++i)
		for (int k = 0; k < board_size; ++k)
		{
			board[i][k] = 0;
			copy[i][k] = 0;
		}

	//Starting tile positions
	int row1 = board_size - 1;
	int col1 = 1;
	int row2 = board_size - 2;
	int col2 = board_size - 1; 

	board[row1][col1] = 2;
	board[row2][col2] = 2;
	copy[row1][col1] = 2;
	copy[row2][col2] = 2;
}

//Sets up board. That is pulls together allocation, board size and fill
void Boarde::setup()
{
	set_board_size();
	allocate();
	fill();
}

//Print array with necessary spacings
void Boarde::print()
{
	for (int i = 0; i < board_size; ++i)
	{
		for (int k = 0; k < board_size; ++k)
		{
			if (board[i][k] == 0)
				cout << empty;
			else
			 	cout << board[i][k];

			cout << "\t";
		}
		cout << "\n\n";
	}
}
//Duplicate array to use for undo
void Boarde::duplicate()
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			copy[i][j] = board[i][j];
		}
	}
}
//Undo
void Boarde::undo()
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			board[i][j] = copy[i][j];
		}							
	}
}

//Introduce a new tile
void Boarde::new_tile()
{
	int row, col;
	bool cond = true;
	while(cond)
	{
		//Finding index position. Random and on edges
		int temp = rand() % 2;
		if (temp)
		{
			row = rand() % board_size;
			int t = rand() % 2;
			if (t)
				col = 0; 
			else
				col = board_size - 1;
		}
		else
		{
			col = rand() % board_size;
			int t = rand() % 2;
			if (t)
				row = 0;
			else
				row = board_size - 1;
		} 

		//If index position not filled
		if (board[row][col] == 0)
		{
			int range = (rand() % 10) + 1;
				if (range < 2)
					board[row][col] = 4;
				else
					board[row][col] = 2;

			cond = false;	
		}
	}
}

//Moves elements up
int Boarde::up()
{
	//Variable that sees if new tile needs to be created after movement.
	//If for example no movement occurs, no new tile has to be created.
	//Same goes for down left and right.
	int t = 0;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (board[i][j] == 0)
			{
				//Empty point so start checking down column
				for (int k = i+1; k < board_size; k++)
				{
					//Found non empty. Move it up
					if (board[k][j] != 0)
					{
						board[i][j] = board[k][j];
						board[k][j] = 0;
						t += 1;
						break;
					}
				}
			}
		}
	}
	return t;
}

//Sums elements that can be summed upwards
int Boarde::sum_up()
{
	int sum = 0;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size - 1; j++)
		{
			//Summation is possible
			if (board[j][i] != 0 && (board[j][i] == board[j+1][i]))
			{
				board[j][i] += board[j+1][i];
				board[j+1][i] = 0;
				sum += board[j][i];
			}
		}
	}
	return sum;
}

//Moves elements down
int Boarde::down()
{
	int t = 0;
	//Start from bottom to top
	for (int i = board_size - 1; i >= 0; i--)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (board[i][j] == 0)
			{
				//Empty point so start checking up column
				for (int k = i - 1; k >= 0; k--)
				{
					//Found non empty, move it down
					if (board[k][j] != 0)
					{
						board[i][j] = board[k][j];
						board[k][j] = 0;
						t+=1;
						break;
					}
				}
			}
		}
	}

	return t;
}

//Downward summation
int Boarde::sum_down()
{
	int sum = 0;
	for (int i = 0; i < board_size; i++)
	{
		//From bottom to top
		for (int j = board_size - 1; j > 0; j--)
		{
			//Equal and nonzero, summation possible
			if (board[j][i] != 0 && board[j][i] == board[j-1][i])
			{
				board[j][i] += board[j-1][i];
				board[j-1][i] = 0;
				sum += board[j][i];
			}
		}
	}

	return sum;
}

//Moves elements left
int Boarde::left()
{
	int t = 0;
	//Left to right checking
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			//Found empty position, start checking to the right
			if (board[i][j] == 0)
			{
				for (int k = j + 1; k < board_size; k++)
				{
					//Found non zero point. Move it leftwards
					if (board[i][k] != 0)
					{
						board[i][j] = board[i][k];
						board[i][k] = 0;
						t+=1;
						break;
					}
				}
			}
		}
	}
	return t;
}

//Leftward sum
int Boarde::sum_left()
{
	int sum = 0;
	//Checking from left to right
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size - 1; j++)
		{
			//Equal non zero points found. Sum them
			if (board[i][j] != 0 && (board[i][j] == board[i][j+1]))
			{
				board[i][j] += board[i][j+1];
				board[i][j+1] = 0;
				sum += board[i][j];
			}
		}
	}

	return sum;
}

//Move elements right
int Boarde::right()
{
	int t = 0;
	//Checking board right to left
	for (int i = 0; i < board_size; i++)
	{
		for (int j = board_size - 1; j >= 0; j--)
		{
			//Found zero element, start checking leftwards
			if (board[i][j] == 0)
			{
				for (int k = j -1; k >= 0; k--)
				{
					//Found non zero element, move it to the right
					if (board[i][k] != 0)
					{
						board[i][j] = board[i][k];
						board[i][k] = 0;
						t = 1;
						break;
					}
				}
			}
		}
	}
	return t;
}

//Rightward sum
int Boarde::sum_right()
{
	int sum = 0;
	//Checking from right to left
	for (int i = 0; i < board_size; i++)
	{
		for (int j = board_size - 1; j > 0; j--)
		{
			//Equal and non zero elements found. Sum them
			if (board[i][j] != 0 && (board[i][j] == board[i][j-1]))
			{
				board[i][j] += board[i][j-1];
				board[i][j-1] = 0;
				sum += board[i][j];
			}
		}
	}
	return sum;
}

//Checks board to see if game is over
bool Boarde::game_over()
{
	//First check for zeros
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			//Zero so game not over
			if (board[i][j] == 0)
				return false;
		}
	}

	//Now check for equal numbers
	//Same in parallel
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size - 1; j++)
		{
			//Equal so game not over
			if (board[i][j] == board[i][j+1])
				return false;
		}
	}
	//Same perpendicular
	for (int i = 0; i < board_size - 1; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			//Equal so game not over
			if (board[i][j] == board[i+1][j])
				return false;
		}
	}	

	cout << " \n GAME OVER \n";
	return true;
}
