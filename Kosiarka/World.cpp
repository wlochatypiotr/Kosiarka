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

void World::Clear()
{
	for (Entity* entity : entities_)
		delete entity;
	entities_.clear();
	Configuration::fruit_ = nullptr;
	sounds_.clear();
}

bool World::IsCollide(const Entity & other)
{
	for (Entity* entity_ptr : entities_)
		if (other.IsCollide(*entity_ptr))
			return true;
	return false;
}

int World::get_size()
{
	return entities_.size();
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

//void World::SetFruit(Entity * entity)
//{
//	if (next_fruit_ == nullptr)
//		next_fruit_ = entity;
//	if (!next_fruit_->is_alive())
//		{
//		delete next_fruit_;		// free memory of eaten fruit	
//		next_fruit_ = entity;	
//		}
//}

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
	//Configuration::fruit_timer_ += deltaTime.asSeconds();
	Configuration::voice_timer_ += deltaTime.asMilliseconds();			
	if (Configuration::voice_timer_ >= random_8_14(eng) * 1000)		//randomize voice interval
	{
		std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::sounds_.get(random_0_2(eng)))); // get random voice
		sound->setAttenuation(0);
		sound->play();
		sounds_.emplace_back(std::move(sound));
		//std::cout << "voice" << "\n";	//helper
		Configuration::voice_timer_ = 0;		//reset voice intervall timer
	}
	//Entity* entity_ptr = *_entities.begin();	// update only player since rest of entities doesnt move
	for (Entity* entity_ptr : entities_)		// formula to update all
	{
		
	entity_ptr->Update(deltaTime);
		auto pos = entity_ptr->getPosition();				//torus space
		sf::Vector2f new_pos;
		if (pos.x > x_)
			entity_ptr->setPosition(sf::Vector2f(0,pos.y));
		if (pos.x < 0)
			entity_ptr->setPosition(sf::Vector2f(x_, pos.y));
		if(pos.y > y_)
			entity_ptr->setPosition(sf::Vector2f(pos.x, 0));
		if(pos.y < 0)
			entity_ptr->setPosition(sf::Vector2f(pos.x, y_));

	}
	//std::cout << Configuration::voice_timer_ << "\n";	//helper
	//std::cout << Configuration::mine_timer_ << "\n";
	//std::cout << Configuration::clock_.getElapsedTime().asSeconds() << "\n";
	//check for collisions

	const auto end = entities_.end();

	for (auto it_i = entities_.begin(); it_i != end; ++it_i)	
	{
		Entity& entity_i = **it_i;
		auto it_j = it_i;			//it_j its an iterator to entity next to entity_i
		it_j++;
		for (; it_j != end; ++it_j)
		{
			Entity& entity_j = **it_j;

			if (entity_i.is_alive() && entity_i.IsCollide(entity_j))
			{
				entity_i.OnDestroy();
				entity_j.OnDestroy();
			}
			if (entity_j.is_alive() && entity_j.IsCollide(entity_i))
				entity_j.OnDestroy();
		}
	}
	for (auto it = entities_.begin(); it != entities_.end();)	//remove dead entities
	{
		if (!(*it)->is_alive())
		{
			delete *it;
			it = entities_.erase(it);
		}
		else
			++it;
	}
	//Player* pPlayer = Configuration::player_;
	//auto player = entities_.begin(); // player nie jest entity no 2 po resecie !
	Entity* pPlayer = Configuration::player_;
	if (Configuration::fruit_->is_alive() && Configuration::fruit_->IsCollide(*pPlayer))
		Configuration::fruit_->OnDestroy();
	//if (next_fruit_ != nullptr && next_fruit_->is_alive() && next_fruit_->IsCollide((*Configuration::player_)))
		//next_fruit_->OnDestroy();
	/*if(!next_fruit_->is_alive())
		delete next_fruit_;
*/
	sounds_.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {		// remove unused sounds
		return sound->getStatus() != sf::Sound::Status::Playing;
	});
	Configuration::score_text_.setString(std::string("SCORE: ") + std::to_string(Configuration::score_)); // update score text


	Configuration::timer_ = Configuration::clock_.getElapsedTime().asSeconds();	
	Configuration::timer_text_.setString(std::to_string(Configuration::timer_));

}

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background_, states);
	//target.draw(Configuration::score_text_, states);
	//target.draw(Configuration::timer_text_, states);
	for (Entity* entity : entities_)
		target.draw(*entity, states);
	target.draw(*Configuration::fruit_);
	//target.draw(Configuration::score_text_, states);
	//target.draw(Configuration::timer_text_, states);
	Configuration::Draw(target);
}
