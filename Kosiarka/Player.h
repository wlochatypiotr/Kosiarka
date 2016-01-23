#pragma once
#include "SFML\Graphics.hpp"

class Player : public sf::Drawable
{
public:
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	Player();

	template<typename ... Args>
	void setPosition(Args&& ... args) {
		_shape.setPosition(std::forward<Args>(args)...);
	}
	sf::Vector2f getPosition();
	void update(sf::Time deltaTime);
	bool _isMoving;
	sf::IntRect getbounds();
	sf::Vector2f _speed;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape _shape;
	
	

};