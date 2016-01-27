#pragma once
#include "Eatable.h"
#include "Player.h"
class Fruit : public Eatable
{
public:
	Fruit(const Fruit&) = delete;
	Fruit& operator= (const Fruit&) = delete;
	using Eatable::Eatable;
	virtual bool IsCollide(const Entity& other) const;
	virtual bool IsCollide(const Player& other) const;
	virtual void Update(sf::Time deltaTime);

};

class Apple : public Fruit
{
public:
	Apple(World& world);
	virtual int get_points() const;
	virtual void OnDestroy();
};

class Pear : public Fruit
{
public:
	Pear(World& world);
	virtual int get_points() const;
	virtual void OnDestroy();
};

class Cherry : public Fruit
{
public:
	Cherry(World& world);
	virtual int get_points() const;
	virtual void OnDestroy();
};