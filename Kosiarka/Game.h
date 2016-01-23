#pragma once
#include "SFML\Graphics.hpp"
#include "Player.h"

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
	Player _player;
	const int _x;			//window size
	const int _y;
	sf::RenderWindow _window;
	//sf::RenderTexture _background;
	sf::Texture _grass;
	sf::Sprite _bcg;
	sf::Image _dirt;
	//sf::Sprite _area;


};