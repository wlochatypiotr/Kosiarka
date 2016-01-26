#pragma once

#include "Entity.h"
#include "Mine.h"
class Entity;
class Mine;
class World : public sf::Drawable
{
public:
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	World(float x, float y);
	~World();

	void add(Entity* entity);
	void clear();
	bool isCollide(const Entity& other);
	int size();

	void add(Configuration::Sounds sound_id);

	const std::list<Entity*> getEntities()const;
	int getX()const;
	int getY()const;
	void update(sf::Time deltaTime);
private:
	std::list<Entity*> _entities;
	
	std::list < std::unique_ptr<sf::Sound>> _sounds;
	sf::Sprite _background;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	const int _x;
	const int _y;
};
