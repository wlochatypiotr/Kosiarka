#pragma once

#include "SFML\Graphics.hpp"
class Level
{
public:
	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
	Level();

private:
	sf::Texture & _foreground_texture;
};