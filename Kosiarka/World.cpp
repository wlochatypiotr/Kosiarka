#include "stdafx.h"
#include "World.h"

World::World(float x, float y) : _x(x), _y(y)
{
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

int World::size()
{
	return _entities.size();
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

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (Entity* entity : _entities)
		target.draw(*entity, states);
}
