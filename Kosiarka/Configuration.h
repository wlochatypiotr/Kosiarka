#pragma once

#include "ResourceManager.h"

class Configuration
{
public:
	Configuration(const Configuration&) = delete;
	Configuration & operator = (const Configuration&) = delete;

	Configuration() = delete;

	static ResourceManager<sf::Texture, int> _textures;
	enum Textures
	{
		Grass_tall,
		Sheep,
		Grass_cut,
		Rock
	};


	static void initialize();

	static void initTextures();
};

