#include "stdafx.h"
#include "Player.h"

Player::Player() :_shape(sf::Vector2f(64,48)), _isMoving(false)
{
	_shape.setFillColor(sf::Color::White);
	_shape.setPosition(100, 100);
	_shape.setOrigin(32, 24);
}

sf::Vector2f Player::getPosition()
{
	return _shape.getPosition();
}

void Player::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();
	if (_isMoving)
	_shape.move(seconds * _speed);
	//sf::Vector2f pos = _shape.getPosition();
	//if (pos.x < 0)
	//{
	//	pos.x = 1600;
	//}
	//
	}

sf::IntRect Player::getbounds()
{
	auto frec = _shape.getGlobalBounds();
	return sf::IntRect(frec.left, frec.top, frec.width, frec.height);
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}
