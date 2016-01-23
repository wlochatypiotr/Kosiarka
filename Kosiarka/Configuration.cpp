#include "stdafx.h"
#include "Configuration.h"

ResourceManager<sf::Texture, int> Configuration::_textures;
void Configuration::initialize()
{
	initTextures();
}


void Configuration::initTextures()
{
	_textures.load(Grass_tall, "media/Textures/GrassTall.jpg", sf::IntRect(0,0,1600,900));
	_textures.load(Grass_cut, "media/Textures/GrassCut.jpg", sf::IntRect(0, 0, 1600, 900));
}
