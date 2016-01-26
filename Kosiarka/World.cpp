#include "stdafx.h"
#include "World.h"

World::World(float x, float y) : _x(x), _y(y)
{
	sf::Texture& texture = Configuration::_textures.get(Configuration::Textures::Grass);
	_background.setTexture(texture);
}

World::~World()
{
	clear();
}

void World::add(Entity * entity)
{
	_entities.push_back(entity);
}

void World::clear()
{
	for (Entity* entity : _entities)
		delete entity;
	_entities.clear();
}

bool World::isCollide(const Entity & other)
{
	for (Entity* entity_ptr : _entities)
		if (other.isCollide(*entity_ptr))
			return true;
	return false;
}

int World::size()
{
	return _entities.size();
}

void World::add(Configuration::Sounds sound_id)
{
	std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::_sounds.get(sound_id)));
	sound->setAttenuation(0);
	sound->play();
	_sounds.emplace_back(std::move(sound));
}

const std::list<Entity*> World::getEntities() const
{
	return _entities;
}

int World::getX() const
{
	return _x;
}

int World::getY() const
{
	return _y;
}

void World::update(sf::Time deltaTime)
{
	Configuration::_mine_timer += deltaTime.asSeconds();
	Configuration::_voice_timer += deltaTime.asMilliseconds();			
	if (Configuration::_voice_timer >= random_8_14(eng) * 1000)		//randomize voice interval
	{
		std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::_sounds.get(random_0_2(eng)))); // get random voice
		sound->setAttenuation(0);
		sound->play();
		_sounds.emplace_back(std::move(sound));
		std::cout << "voice" << "\n";	//helper
		Configuration::_voice_timer = 0;		//reset voice intervall timer
	}
	Entity* entity_ptr = *_entities.begin();	// update only player since rest of entities doesnt move
	//for (Entity* entity_ptr : _entities)		// formula to update all
	//{
		
	entity_ptr->update(deltaTime);
		auto pos = entity_ptr->getPosition();				//torus space
		sf::Vector2f new_pos;
		if (pos.x > _x)
			entity_ptr->setPosition(sf::Vector2f(0,pos.y));
		if (pos.x < 0)
			entity_ptr->setPosition(sf::Vector2f(_x, pos.y));
		if(pos.y > _y)
			entity_ptr->setPosition(sf::Vector2f(pos.x, 0));
		if(pos.y < 0)
			entity_ptr->setPosition(sf::Vector2f(pos.x, _y));

	//}
	std::cout << Configuration::_voice_timer << "\n";	//helper
	std::cout << Configuration::_mine_timer << "\n";

	//check for collisions

	const auto end = _entities.end();

	for (auto it_i = _entities.begin(); it_i != end; ++it_i)	
	{
		Entity& entity_i = **it_i;
		auto it_j = it_i;			//it_j its an iterator to entity next to entity_i
		it_j++;
		for (; it_j != end; ++it_j)
		{
			Entity& entity_j = **it_j;

			if (entity_i.isAlive() && entity_i.isCollide(entity_j))
				entity_i.onDestroy();

			if (entity_j.isAlive() && entity_j.isCollide(entity_i))
				entity_j.onDestroy();
		}
	}
	for (auto it = _entities.begin(); it != _entities.end();)
	{
		if (!(*it)->isAlive())
		{
			delete *it;
			it = _entities.erase(it);
		}
		else
			++it;
	}


	_sounds.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {		// remove unused sounds
		return sound->getStatus() != sf::Sound::Status::Playing;
	});
}

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_background, states);
	for (Entity* entity : _entities)
		target.draw(*entity, states);
}
