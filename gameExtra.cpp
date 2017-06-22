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
#include <fstream>
#include "GameExtra.h"
#include "BoardExtra.h"
using namespace std;

//Default constructor and destructor, use reasonable values
Gamee::Gamee()
{
	score = 0;
	username = " ";
	score_ray = NULL;
	name_ray = NULL;
	temp_count = 0;
	score_back = 0;
}
Gamee::~Gamee()
{
	delete [] score_ray;
	delete [] name_ray;
}

//Setter and getter functions for member attributes
void Gamee::set_score(int s)
{
	score += s;
}
void Gamee::set_username()
{
	string n;
	cout << "Enter your username: \n";
	cin >> n;

	username = n;
}
int Gamee::get_score()
{
	return score;
}
string Gamee::get_username()
{
	return username;
}

//Welcoming function. Prints information to user
void Gamee::welcome()
{
	cout << "\nWelcome to 2048!\n";
	cout << "Commands are as follow:\n";
	cout << "w for up\n";
	cout << "a for left\n";
	cout << "s for down\n";
	cout << "d for right\n";
	cout << "h to see top-5 high scores\n";
	cout << "r to restart game\n";
	cout << "q to quit\n\n";
}

//Input validation function that returns a character, corresponding to
//user input
char Gamee::input_validator()
{
	//String, handles cases where user enters more than one character
	string n;
	cout << "Enter your move: \n";
	cin >> n;

	while((n!="w")&&(n!="a")&&(n!="s")&&(n!="d")&&(n!="h")&&(n!="q")&&(n!="r")
		&&(n!="u"))
	{
		cout << "Enter a valid move: \n";
		cin >> n;
	}
	//Convert to char
	char a = n[0];
	return a;
}

//Input translator. Function that pulls game together and calls
//required functions. t and s are helper variables that figure
//out if a new tile should be created or not.
void Gamee::user_input(Boarde &obj, bool &quit)
{
	char n = input_validator();
	int t, s = 0;
	switch(n)
	{
		case 'w':
			//movement-sum-movement in order to
			//take into account all positions
			obj.duplicate(); 
			t = obj.up();
			s = obj.sum_up();
			score += s;
			score_back += s;
			t += obj.up();
			if (t > 0 || s > 0)
				obj.new_tile(); //Movement changed board so tile created
			break;
		case 'a':
			obj.duplicate(); 
			t = obj.left();
			s = obj.sum_left();
			score += s;
			score_back += s;
			t += obj.left();
			if (t > 0 || s > 0)
				obj.new_tile();
			break;
		case 's':
			obj.duplicate(); 
			t = obj.down();
			s = obj.sum_down();
			score += s;
			score_back += s;
			t += obj.down();
			if (t > 0 || s > 0)
				obj.new_tile();
			break;
		case 'd':
			obj.duplicate(); 
			t = obj.right();
			s = obj.sum_right();
			score += s;
			score_back += s;
			t += obj.right();
			if (t > 0 || s > 0)	
				obj.new_tile();
			break;
		case 'h':
			high_score();
			break;
		case 'r':
			score = 0;
			obj.restart();
			break;
		case 'u':
			obj.undo();
			score-=score_back;
			break;
		default:
			//Quit game
			quit = true;
			cout << "Thanks for playing! \n";
	}
}

//Counts number of lines of highscore file
void Gamee::file_lines()
{
	temp_count = 0;
	string temp_line;
	infile.open(NAME);
	if (!infile.is_open()) //file had not been opened before
		cerr << "Creating file...\n";

	while (getline(infile, temp_line))
		temp_count++;
	infile.close();	
}

//Prints top 5 high score files.
void Gamee::high_score()
{
	file_lines();
	int ctr = 0;
	//Temporary arrays
	int s[6];
	string n[6];

	cout << "\nTop 5 Highscores \n";
	infile.open(NAME);
	if (!infile.is_open())
		cerr << "Error gathering highscores: ";

	//Print only 5 or less than 5 scores
	while (ctr < temp_count && ctr < 6)
	{
		infile >> n[ctr];
		infile >> s[ctr];
		ctr++;
	}
	infile.close();

	if (ctr <= 1)
		cout << "No Recorded Highscores \n";
	else
	{
		for (int i = 0; i < ctr-1; ++i)
		{
			cout << n[i] << ": " << s[i] << endl;
		}
	}

	cout << endl;
}

//Temporary score, printed after every move
void Gamee::temp_score()
{
	cout << "Current score: " << score << endl; 
}

//Reads current scores from file to arrays of scores and names.
void Gamee::file_reader()
{
	infile.open(NAME);
	if (!infile.is_open())
		cerr << "Error opening file 2\n";

	int ctr = 0;
	while (!infile.eof() && ctr < temp_count - 1)
	{
		infile >> name_ray[ctr];
		infile >> score_ray[ctr];
		ctr++;
	}
	infile.close();
}

//Writes arrays to file at a sorted fashion(Higher first)
void Gamee::file_writer()
{
	outfile.open(NAME);
	if (!outfile.is_open())
		cerr << "Error opening file 3\n";

	//Print higher scores first
	for (int i = 0; i < temp_count; ++i)
	{
		int temp = 0;
		int t = 0;

		for (int k = 0; k < temp_count; k++)
		{
			if (score_ray[k] >= temp)
			{
				temp = score_ray[k];
				t = k;
			}
		}
		outfile << name_ray[t] << ' ';
		outfile << score_ray[t] << endl;

		//Discard already used scores and names to avoid confusion
		score_ray[t] = -(temp_count - i);
		name_ray[t] = " ";
	}
	outfile << -1;
	outfile.close();	
}

//Pulls all functions related to the high score file together
void Gamee::score_file()
{
	//Get lines
	file_lines();
	//First time opening file so can add only this run's score and name
	if (temp_count == 0)
	{
		outfile.open(NAME);
		if (!outfile.is_open())
			cerr << "Error opening file 3\n";

		outfile << username << ' ';
		outfile << score << endl;
		outfile << -1;

		outfile.close();
	}
	else
	{
		//Highscore file had been created before
		score_ray = new int[temp_count];
		name_ray = new string[temp_count];
		
		file_reader();

		//Add last runs score and name
		name_ray[temp_count - 1] = username;
		score_ray[temp_count - 1] = score;

		file_writer();
	}
}