#include "stdafx.h"
#include "Game.h"
#include "Configuration.h"

Game::Game(int x , int y ) : _x(x), _y(y), _window(sf::VideoMode(_x, _y), "Koasiarka"), _World(x, y)//, _area(0,0,x,y)
{
	_window.setVerticalSyncEnabled(true);
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
	_window.draw(_World);
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
			//else if (event.key.code == sf::Keyboard::Up)
			//{
			//	Configuration::player->_isMoving = true;
			//	//Configuration::player->_speed = sf::Vector2f(0, -100);
			//}
			///*else if (event.key.code == sf::Keyboard::Down)
			//{
			//	Configuration::player->_isMoving = true;
			//	Configuration::player->_speed = sf::Vector2f(0, 100);
			//}*/
			//else if (event.key.code == sf::Keyboard::Left)
			//{
			//	Configuration::player->rotation = -1;
			//}
			//else if (event.key.code == sf::Keyboard::Right)
			//{
			//	Configuration::player->rotation = 1;
			//}
		}
		
	}
	//Configuration::player->processEvents();
}

void Game::update(sf::Time deltaTime)
{
	if (Configuration::player == nullptr)
	{
		Configuration::player = new Player(_World);
		Configuration::player->setPosition(_World.getX() / 2, _World.getY() / 2);
		_World.add(Configuration::player);
	}
	if (Configuration::_mine_timer > Configuration::_mine_interval) // mine adding
	{
		//res_1600(eng);
		//res_900(eng);
		Entity* mine(new Mine(_World));
		mine->setPosition(sf::Vector2f(res_1600(eng), res_900(eng)));
		while (_World.isCollide(*mine))
		{
			mine->setPosition(sf::Vector2f(res_1600(eng), res_900(eng))); // ujednolicic randomy
		}
		_World.add(mine);
		Configuration::_mine_timer = 0;
	}
	//Configuration::player->update(deltaTime);
	_World.update(deltaTime);
	
}

const int Game::getX() const
{
	return _x;
}

const int Game::getY() const
{
	return _y;
}
