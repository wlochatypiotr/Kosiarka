#include "stdafx.h"
#include "Fruit.h"

bool Fruit::IsCollide(const Entity & other) const
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
}
