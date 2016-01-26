#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"
#include "World.h"

class Player;
class Game
{
public:
	Game(const Game&) = delete;
	Game& operator= (const Game&) = delete;

	Game(int x = 1600, int y = 900);

	void run(int min_fps);
	void render();
	void processEvents();
	void update(sf::Time deltaTime);
	const int getX() const; 
	const int getY() const;
private:
	const int _x;			//window size
	const int _y;

	sf::RenderWindow _window;
	World _World;
};