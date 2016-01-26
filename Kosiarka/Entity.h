#pragma once
#include "Configuration.h"
#include "SFML\Graphics.hpp"
#include "Collision.h"

class World;
class Entity : public sf::Drawable
{
public:
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	Entity(Configuration::Textures tex_id, World& world);
	virtual ~Entity();

	virtual bool isAlive() const; //returns state of Entity
	const sf::Vector2f getPosition() const;
	template <typename ... Args>
	void setPosition(Args&& ... args);	// self explainatory
	virtual bool isCollide(const Entity& other) const = 0;

	virtual void update(sf::Time deltaTime) = 0;
	virtual void onDestroy();
protected:

	friend class Player;
	friend class Mine;
	sf::Sprite _sprite;
	sf::Vector2f _speed;
	World& _world;
	bool _Alive;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
template <typename ... Args>
void Entity::setPosition(Args&& ... args) {
	_sprite.setPosition(std::forward<Args>(args)...);
}