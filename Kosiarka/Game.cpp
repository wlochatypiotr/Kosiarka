#include "stdafx.h"
#include "Game.h"
#include "Configuration.h"

Game::Game(int x , int y ) : _x(x), _y(y), _window(sf::VideoMode(_x, _y), "Koasiarka")//, _area(0,0,x,y)
{
	_window.setVerticalSyncEnabled(true);
	Player _player;
	_grass = Configuration::_textures.get(Configuration::Textures::Grass_tall);	//reference to texture
	_bcg.setTexture(_grass);	// big sprite with long grass
	_dirt.create(32, 32, sf::Color::Blue);
	//sf::Sprite _area(Configuration::_textures.get(Configuration::Textures::Grass_cut), _player.getbounds()); // sprite with cut grass
	
}

void Game::run(int min_fps)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / min_fps);
	while (_window.isOpen()) {
		processEvents();
		timeSinceLastUpdate = clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			update(TimePerFrame);
		}
		update(timeSinceLastUpdate);
		render();
	}
}

void Game::render()
{
	_window.clear();
	_window.draw(_bcg);
	
	_window.draw(_player);
	//_window.draw(_area);
	_window.display();
}


void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();
			else if (event.key.code == sf::Keyboard::Up)
			{
				_player._isMoving = true;
				_player._speed = sf::Vector2f(0, -100);
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				_player._isMoving = true;
				_player._speed = sf::Vector2f(0, 100);
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				_player._isMoving = true;
				_player._speed = sf::Vector2f(-100, 0);
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				_player._isMoving = true;
				_player._speed = sf::Vector2f(100, 0);
			}
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	//sf::Sprite temp(Configuration::_textures.get(Configuration::Textures::Grass_cut), _player.getbounds());
	//_area = temp;
	//_area.move(_player.getPosition());
	_player.update(deltaTime);
	_grass.update(_dirt, _player.getPosition().x, _player.getPosition().y);	// draw cut grass
}

const int Game::getX() const
{
	return _x;
}

const int Game::getY() const
{
	return _y;
}
