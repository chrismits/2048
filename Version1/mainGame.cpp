
#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Game.h"
#include "Board.h"
using namespace std;

int main()
{
	//Starting up game
	srand(time(NULL));
	bool over = false;
	bool quit = false;
	Game game;
	Board board;
	game.welcome();
	board.setup();
	
	//Main game loop
	while(!over && !quit)
	{
		game.temp_score();
		board.print();
		game.user_input(board,quit);
		over = board.game_over();
	}

	//Finishing up game
	game.set_username();
	game.score_file();
	game.high_score();

	return 0;
}
