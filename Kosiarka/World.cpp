#include "stdafx.h"
#include "World.h"

World::World(int x, int y) : x_(x), y_(y)
{
	sf::Texture& texture = Configuration::textures_.get(Configuration::Textures::GRASS);
	background_.setTexture(texture);
}

World::~World()
{
	Clear();
}

void World::Add(Entity * entity)
{
	entities_.push_back(entity);
}

void World::AddMine(Entity * entity)
{
	mines_.push_back(entity);
}

void World::Clear()
{
	for (Entity* entity : entities_)
		delete entity;
	entities_.clear();
}

bool World::IsCollide(const Entity & other)
{
	for (Entity* entity_ptr : mines_)
		if (other.IsCollide(*entity_ptr))
			return true;

	return false;
}


void World::Add(Configuration::Sounds sound_id)
{
	std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds_.get(sound_id)));
	sound->setAttenuation(0);
	sound->play();
	sounds_.emplace_back(std::move(sound));
}

const std::list<Entity*> World::get_entities() const
{
	return entities_;
}

int World::get_x() const
{
	return x_;
}

int World::get_y() const
{
	return y_;
}

void World::Update(sf::Time deltaTime)
{
	Configuration::mine_timer_ += deltaTime.asSeconds();

	Configuration::voice_timer_ += deltaTime.asMilliseconds();			
	if (Configuration::voice_timer_ >= random_8_14(eng) * 1000)		//randomize voice interval
	{
		Add(Configuration::Sounds (random_0_2(eng)));
		Configuration::voice_timer_ = 0;		//reset voice interval timer
	}

		//update player
	Configuration::player_->Update(deltaTime);
		auto pos = Configuration::player_->getPosition();				//torus space
		if (pos.x > x_)
			Configuration::player_->setPosition(sf::Vector2f(0,pos.y));
		if (pos.x < 0)
			Configuration::player_->setPosition(sf::Vector2f(x_, pos.y));
		if(pos.y > y_)
			Configuration::player_->setPosition(sf::Vector2f(pos.x, 0));
		if(pos.y < 0)
			Configuration::player_->setPosition(sf::Vector2f(pos.x, y_));

	
	//check for collisions
	const auto end = mines_.end();
	
	for (auto it = mines_.begin(); it != end; ++it)
	{
		Entity& mine = **it;
		if (Configuration::player_->is_alive() && Configuration::player_->IsCollide(mine))
		{
			Configuration::player_->OnDestroy();
			mine.OnDestroy();
		}
	}

	//Check for collision with fruit
	if (Configuration::player_->is_alive() && Configuration::player_->IsCollide(*Configuration::fruit_))
		Configuration::fruit_->OnDestroy();

	//remove dead mines for the list
	for (auto it = mines_.begin(); it != mines_.end();)
	{
		if (!(*it)->is_alive())
		{							
			it = mines_.erase(it);
		}
		else
			++it;
	}
	//remove destroyed mines, eaten fruits and free memory
	for (auto it = entities_.begin(); it != entities_.end();)	
	{
		if (!(*it)->is_alive())
		{
			delete *it;			// free memory
			it = entities_.erase(it);
		}
		else
			++it;
	}

	sounds_.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {		// remove unused sounds
		return sound->getStatus() != sf::Sound::Status::Playing;
	});

	//update score string
	Configuration::score_text_.setString(std::string("SCORE: ") + std::to_string(Configuration::score_)); // update score text


	Configuration::timer_ = Configuration::clock_.getElapsedTime().asSeconds();	
	Configuration::timer_text_.setString(std::to_string(Configuration::timer_));

}

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background_, states);

	for (Entity* entity : entities_)
		target.draw(*entity, states);
	Configuration::Draw(target);
}
