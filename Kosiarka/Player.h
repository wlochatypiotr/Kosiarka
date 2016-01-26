#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Entity.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Player : public Entity
{
	friend class Game;
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	Player(World& world);

	virtual bool isCollide(const Entity& other) const override;
	virtual void update(sf::Time deltaTime) override;
	void processEvents();

	virtual void onDestroy();

private:
	bool _isMoving;
	int rotation;

};