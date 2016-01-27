#include "stdafx.h"
#include "Game.h"
#include "Configuration.h"
int main()
{
	Configuration::Initialize();
	Game game;
	game.Run(60);
	return 0;
}