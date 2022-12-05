#include <SFML/Graphics.hpp>
#include <iostream>
#include "Meni.h"
#include "Game.h"
#include <time.h>

using namespace std;

int main()
{
	srand(time(nullptr));
	
	Game game;

	game.run();

	return 0;
}