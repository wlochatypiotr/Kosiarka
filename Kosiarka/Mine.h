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

	virtual bool IsCollide(const Entity& other) const override;
	virtual void Update(sf::Time deltaTime);
	virtual void OnDestroy();
};