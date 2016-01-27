#include "stdafx.h"
#include "Player.h"
Player::Player(World& world) : Entity(Configuration::Textures::SHEEP, world), is_moving_(false), rotation_(0)
{
}



bool Player::IsCollide(const Entity & other) const
{
	return Collision::CircleTest(sprite_, other.sprite_);
	//return	Collision::PixelPerfectTest(sprite_, other.sprite_);
	//return Collision::BoundingBoxTest(sprite_, other.sprite_);
}

void Player::Update(sf::Time deltaTime)
{
	ProcessEvents();
	float seconds = deltaTime.asSeconds();
	if (rotation_ != 0)
	{
		float angle = rotation_ * 250 * seconds;
		sprite_.rotate(angle);
	}
	if (is_moving_)
	{
		float angle = sprite_.getRotation() / 180 * M_PI - M_PI / 2;
		speed_ = sf::Vector2f(Configuration::max_speed_ * std::cos(angle), Configuration::max_speed_ * std::sin(angle));
		//speed_ += sf::Vector2f(std::cos(angle), std::sin(angle)) * 100.f * seconds; ship like movement
	}
	sprite_.move(seconds * speed_);
	rotation_ = 0;
	//_isMoving = 0;
}

void Player::ProcessEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		is_moving_ = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rotation_ = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rotation_ = 1;
}
	

void Player::OnDestroy()
{
	--Configuration::player_lives_;
	this->setPosition(sf::Vector2f(world_.get_x() / 2, world_.get_y() / 2)); // works for fruits too ! 
}


