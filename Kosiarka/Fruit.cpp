#include "stdafx.h"
#include "Fruit.h"
#include "World.h"

bool Fruit::IsCollide(const Entity & other) const
{
	return Collision::CircleTest(sprite_, other.sprite_);
}
bool Fruit::IsCollide(const Player & other) const
{
	return Collision::CircleTest(sprite_, other.sprite_);
}

void Fruit::Update(sf::Time deltaTime)
{
}

Apple::Apple(World & world) : Fruit(Configuration::Textures::APPLE, world)
{
}

int Apple::get_points() const
{
	return 50;
}

void Apple::OnDestroy()
{
	Fruit::OnDestroy();
	Configuration::IncreaseScore(get_points());
	world_.Add(Configuration::Sounds::EAT_APPLE);
}

Pear::Pear(World & world) : Fruit(Configuration::Textures::PEAR, world)
{
}

int Pear::get_points() const
{
	return 80;
}

void Pear::OnDestroy()
{
	Fruit::OnDestroy();
	Configuration::IncreaseScore(get_points());
	world_.Add(Configuration::Sounds::EAT_PEAR);
}

Cherry::Cherry(World & world) : Fruit(Configuration::Textures::CHERRY, world)
{
}

int Cherry::get_points() const
{
	return 150;
}

void Cherry::OnDestroy()
{
	Fruit::OnDestroy();
	Configuration::IncreaseScore(get_points());
	world_.Add(Configuration::Sounds::EAT_CHERRY);
}
