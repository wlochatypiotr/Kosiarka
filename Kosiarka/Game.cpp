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
	if (Configuration::IsGameOver())
		window_.draw(Configuration::score_text_);
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
		}
		//	if (Configuration::IsGameOver())
		//	{
		//		if (event.type == sf::Event::KeyPressed) //keyboard input
		//			Reset();
		//	}
		//	else
		//	{
		//		if (Configuration::player_ != nullptr)
		//			Configuration::player_->ProcessEvents();
		//	}
		//}
		//if (!Configuration::IsGameOver() && Configuration::player_ != nullptr)
		//	Configuration::player_->ProcessEvents();
	}
}


void Game::Update(sf::Time deltaTime)
{
	if (!Configuration::IsGameOver())
	{
		if (Configuration::player_ == nullptr)
		{
			Configuration::player_ = new Player(world_);
			Configuration::player_->setPosition(sf::Vector2f(world_.get_x() / 2, world_.get_y() / 2));
			world_.Add(Configuration::player_);
		}
		if (Configuration::fruit_ == nullptr)
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
				fruit->setPosition(sf::Vector2f(random_0_1600(eng), random_0_900(eng)));
			}
			Configuration::fruit_ = fruit;
			world_.Add(fruit);
		}
	

		//if (world_.next_fruit_ == nullptr ||Eatable::count_ == 0)	//add new fruit when there is none
		////if (Configuration::fruit_timer_ > Configuration::fruit_interval_) // fruit adding at fixed time
		//{
		//	Entity* fruit = nullptr;
		//	int i = random_0_2(eng);
		//	switch (i)
		//	{
		//	case 0:
		//		fruit = new Apple(world_);
		//		break;
		//	case 1:
		//		fruit = new Pear(world_);
		//		break;
		//	case 2:
		//		fruit = new Cherry(world_);
		//		break;
		//	}
		//	fruit->setPosition(sf::Vector2f(random_0_1600(eng), random_0_900(eng)));
		//	while (world_.IsCollide(*fruit))
		//	{
		//		fruit->setPosition(sf::Vector2f(random_0_1600(eng), random_0_900(eng))); // ujednolicic randomy
		//	}
		//	world_.SetFruit(fruit);
		//	//Configuration::fruit_timer_ = 0;
		//}
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
}

void Game::Reset()
{
	world_.Clear();
	Configuration::player_ = nullptr;
	Configuration::fruit_ = nullptr;
	Configuration::Reset();
}

const int Game::get_x() const
{
	return x_;
}

const int Game::get_y() const
{
	return y_;
}
