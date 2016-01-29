#pragma once

#include "Entity.h"
#include "Mine.h"
#include "Fruit.h"
class Entity;
class Mine;
class World : public sf::Drawable
{
public:
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	World(int x, int y);
	~World();

	void Add(Entity* entity);
	void Clear();	//Entities
	bool IsCollide(const Entity& other);

	void Add(Configuration::Sounds sound_id);

	const std::list<Entity*> get_entities()const;
	int get_size();			//entities
	int get_x()const;
	int get_y()const;
	void Update(sf::Time deltaTime);
private:
	std::list<Entity*> entities_;
	
	std::list < std::unique_ptr<sf::Sound>> sounds_;
	sf::Sprite background_;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	const int x_;
	const int y_;
};
