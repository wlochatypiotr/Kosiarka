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

	virtual bool is_alive() const; //returns state of Entity
	const sf::Vector2f getPosition() const;
	template <typename ... Args>
	void setPosition(Args&& ... args);	// self explainatory
	virtual bool IsCollide(const Entity& other) const = 0;

	virtual void Update(sf::Time deltaTime) = 0;
	virtual void OnDestroy();
protected:

	friend class Player;
	friend class Mine;
	friend class Fruit;
	sf::Sprite sprite_;
	sf::Vector2f speed_;
	World& world_;
	bool alive_;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
template <typename ... Args>
void Entity::setPosition(Args&& ... args) {
	sprite_.setPosition(std::forward<Args>(args)...);
}