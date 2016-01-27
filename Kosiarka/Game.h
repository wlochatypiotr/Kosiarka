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

	void Run(int min_fps);
	void Render();
	void ProcessEvents();
	void Update(sf::Time deltaTime);

	void Reset();
	const int get_x() const; 
	const int get_y() const;
private:
	const int x_;			//window size
	const int y_;

	sf::RenderWindow window_;
	World world_;
};