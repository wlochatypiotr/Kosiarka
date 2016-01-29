#include "stdafx.h"
#include "Game.h"
#include "Configuration.h"

Game::Game(int x , int y ) : x_(x), y_(y), window_(sf::VideoMode(x_, y_), "Koasiarka"), world_(x, y)//, _area(0,0,x,y)
{
	window_.setVerticalSyncEnabled(true);
}

void Game::Run(int min_fps)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time TimePerFrame = sf::seconds(1.f / min_fps);
	while (window_.isOpen()) {
		ProcessEvents();
		timeSinceLastUpdate = clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			Update(TimePerFrame);
		}
 		Update(timeSinceLastUpdate);
		Render();
	}
}

void Game::Render()
{
	window_.clear();
	window_.draw(world_);
	window_.display();
}


void Game::ProcessEvents()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				window_.close();
			//else if (event.key.code == sf::Keyboard::Up)
			//{
			//	Configuration::player->_isMoving = true;
			//	//Configuration::player->speed_ = sf::Vector2f(0, -100);
			//}
			///*else if (event.key.code == sf::Keyboard::Down)
			//{
			//	Configuration::player->_isMoving = true;
			//	Configuration::player->speed_ = sf::Vector2f(0, 100);
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
	//Configuration::player->ProcessEvents();
}

void Game::Update(sf::Time deltaTime)
{
	if (Configuration::player_ == nullptr)
	{
		Configuration::player_ = new Player(world_);
		Configuration::player_->setPosition(sf::Vector2f(world_.get_x() / 2, world_.get_y() / 2));
		world_.Add(Configuration::player_);
	}
	if(Eatable::count_ == 0)	//add new fruit when there is none
	//if (Configuration::fruit_timer_ > Configuration::fruit_interval_) // fruit adding at fixed time
	{
		Entity* fruit = nullptr;
		int i = random_0_2(eng);
		switch (i)
		{
		case 0:
			fruit = new Apple(world_);
			break;
		case 1:
			fruit = new Pear(world_);
			break;
		case 2:
			fruit = new Cherry(world_);
			break;
		}
		fruit->setPosition(sf::Vector2f(random_0_1600(eng), random_0_900(eng)));
		while (world_.IsCollide(*fruit))
		{
			fruit->setPosition(sf::Vector2f(random_0_1600(eng), random_0_900(eng))); // ujednolicic randomy
		}
		world_.Add(fruit);
		//Configuration::fruit_timer_ = 0;
	}
	if (Configuration::mine_timer_ > Configuration::mine_interval_) // mine adding
	{
	
		Entity* mine(new Mine(world_));
		mine->setPosition(sf::Vector2f(random_0_1600(eng), random_0_900(eng)));
		while (world_.IsCollide(*mine))
		{
			mine->setPosition(sf::Vector2f(random_0_1600(eng), random_0_900(eng))); 
		}
		world_.Add(mine);
		Configuration::mine_timer_ = 0;
	}
	//Configuration::player->update(deltaTime);
	world_.Update(deltaTime);
}

const int Game::get_x() const
{
	return x_;
}

const int Game::get_y() const
{
	return y_;
}
