#include <cstdlib>
#include <stdio.h>
#include <time.h>

#include "Game.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	Game& game = Game::game();
	game.init();
	game.start(); 

	delete& game;

	return 0;
}