#include "stdafx.h"
#include "Entity.h"

Entity::Entity(Configuration::Textures tex_id, World & world) : world_(world), alive_(true)
{
	sf::Texture& texture = Configuration::textures_.get(tex_id);
	sprite_.setTexture(texture);
	sprite_.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

Entity::~Entity()
{
}

bool Entity::is_alive() const
{
	return alive_;
}

const sf::Vector2f Entity::getPosition() const
{
	return sprite_.getPosition();
}

void Entity::OnDestroy()
{
	alive_ = false;
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}
