#include "stdafx.h"
#include "Mine.h"

Mine::Mine(World& world) :  Entity(Configuration::Textures::Mine, world)
{

}

bool Mine::isCollide(const Entity & other) const
{
	return Collision::CircleTest(_sprite, other._sprite);
	 //return	Collision::PixelPerfectTest(_sprite, other._sprite);
}

void Mine::update(sf::Time deltaTime)
{
}

void Mine::onDestroy()
{
	Entity::onDestroy();
	_world.add(Configuration::Sounds::Explosion);
}
