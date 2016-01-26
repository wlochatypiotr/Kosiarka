#include "stdafx.h"
#include "Player.h"

Player::Player(World& world) : Entity(Configuration::Textures::Sheep, world), _isMoving(false), rotation(0)
{
}



bool Player::isCollide(const Entity & other) const
{
	return Collision::CircleTest(_sprite, other._sprite);
	//return	Collision::PixelPerfectTest(_sprite, other._sprite);
	//return Collision::BoundingBoxTest(_sprite, other._sprite);
}

void Player::update(sf::Time deltaTime)
{
	processEvents();
	float seconds = deltaTime.asSeconds();
	if (rotation != 0)
	{
		float angle = rotation * 250 * seconds;
		_sprite.rotate(angle);
	}
	if (_isMoving)
	{
		float angle = _sprite.getRotation() / 180 * M_PI - M_PI / 2;
		_speed = sf::Vector2f(Configuration::MAX_SPEED * std::cos(angle), Configuration::MAX_SPEED * std::sin(angle));
		//_speed += sf::Vector2f(std::cos(angle), std::sin(angle)) * 100.f * seconds; ship like movement
	}
	_sprite.move(seconds * _speed);
	rotation = 0;
	//_isMoving = 0;
}

void Player::processEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rotation = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rotation = 1;
	//else if(sf::Keyboard::)
}
	

void Player::onDestroy()
{
}


