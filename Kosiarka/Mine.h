#pragma once
#include "Entity.h"
#include "World.h"
class Mine : public Entity
{
	friend class Game;
public:
	Mine(const Mine&) = delete;
	Mine& operator=(const Mine&) = delete;

	Mine(World& world);

	virtual bool isCollide(const Entity& other) const override;
	virtual void update(sf::Time deltaTime);
	virtual void onDestroy();
};