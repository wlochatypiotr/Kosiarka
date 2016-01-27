#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Entity.h"
#include "World.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
class World;
class Player : public Entity
{
	friend class Game;
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	Player(World& world);

	virtual bool IsCollide(const Entity& other) const override;
	virtual void Update(sf::Time deltaTime) override;
	void ProcessEvents();

	virtual void OnDestroy();

private:
	bool is_moving_;
	int rotation_;

};