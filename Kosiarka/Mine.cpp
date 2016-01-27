#include "stdafx.h"
#include "Mine.h"

Mine::Mine(World& world) :  Entity(Configuration::Textures::MINE, world)
{

}

bool Mine::IsCollide(const Entity & other) const
{
	return Collision::CircleTest(sprite_, other.sprite_);
	 //return	Collision::PixelPerfectTest(sprite_, other.sprite_);
}

void Mine::Update(sf::Time deltaTime)
{
}

void Mine::OnDestroy()
{
	Entity::OnDestroy();
	world_.Add(Configuration::Sounds::EXPLOSION);
}
