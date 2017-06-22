/*******************************
* COMP 11 Spring 2017
* Homework 6
* Christos-Nikolaos Mitsopoulos
* Signoff by [Laney Strange] [04/11/2017]
* EXTRA CREDIT
********************************/

#include <iostream>
#include <fstream>
#include "BoardExtra.h"
using namespace std;

#ifndef GAMEEXTRA_H_
#define GAMEEXTRA_H_

//File name
const string NAME = "highscores.txt";

class Gamee
{
private:
	//User Score
	int score;
	//Undo
	int score_back;
	//Number of lines of score file
	int temp_count;
	//Name of user
	string username;
	//Variable to read from high scores file
	ifstream infile;
	//Variable to write to high scores file
	ofstream outfile;
	//Dynamic 1D array of scores
	int* score_ray;
	//Dynamic 1D array of names
	string* name_ray;

public:
	//Class constructor. Initializes variables
	Gamee();
	//Class destructor. Deallocates arrays of scores and names
	~Gamee();

	//Sets user score. Input: integer that represents score
	void set_score(int);
	//Gets user score. Output: score (int)
	int get_score();
	//Ask user for his name at the end and set it to username
	void set_username();
	//Get username. Output: username(string)
	string get_username();
	//Extra credit undo score
	void set_score_back(int);
	
	//Welcome print statement that explains to the user the commands
	void welcome();
	//Reads and displays top 5 high scores from files and prints them to screen
	void high_score();

	//Keeps track of current score and displays it to user after every move
	void temp_score();
	//input validation function. Returns the user input
	char input_validator();
	//Calls necessary functions based on input. This is the function that pulls
	//Everything together. Inputs: board object and boolean both by reference
	void user_input(Boarde &obj, bool &);

	//Counts number of lines of high score file. Returns that number.
	void file_lines();
	//Reads from already created file into arrays
	void file_reader();
	//Writes from arrays to file accordingly
	void file_writer();
	//Prompt user for his name, write scores from array to file, sort file.
	void score_file();
};

#endif
