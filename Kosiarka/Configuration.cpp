#include "stdafx.h"
#include "Configuration.h"
#include "Random.h"
#include "Collision.h"

// Resource Managers
ResourceManager<sf::Texture, int> Configuration::_textures;
ResourceManager<sf::Music, int> Configuration::_music;
ResourceManager<sf::SoundBuffer, int> Configuration::_sounds;

//stores interval between sheep's voice
float Configuration::_voice_timer;

//defines game difficulty
int Configuration::MAX_SPEED;
float Configuration::_mine_timer;
float Configuration::_mine_interval = 0.1;
sf::Clock Configuration::clock;

Player* Configuration::player = nullptr;

void Configuration::initialize()
{
	MAX_SPEED = 200;
	initTextures();
	initSounds();
	initMusic();

	_music.get(Configuration::Music::Theme).setLoop(true);
	_music.get(Configuration::Music::Theme).play();
}


void Configuration::initTextures()
{
	/* sf::Texture mine;
	Collision::CreateTextureAndBitmask(mine, "Media/Textures/Mine.png");*/

	_textures.load(Fruit1, "Media/Textures/apple.png");
	_textures.load(Fruit2, "Media/Textures/pear.png");
	_textures.load(Fruit3, "Media/Textures/cherry.png");
	_textures.load(Sheep, "Media/Textures/Sheep.png");
	_textures.load(Grass, "media/Textures/Grass.jpg");
	_textures.load(Mine, "Media/Textures/Mine.png");	
}

void Configuration::initMusic()
{
	_music.load(Theme, "media/Sounds/Cipher2.ogg");
}

void Configuration::initSounds()
{
	_sounds.load(Configuration::Sounds::Voice1, "Media/Sounds/Voice1.ogg");
	_sounds.load(Configuration::Sounds::Voice2, "Media/Sounds/Voice2.ogg");
	//_sounds.load(Configuration::Sounds::Voice3, "Media/Sounds/Voice3.ogg");
	_sounds.load(Configuration::Sounds::Voice4, "Media/Sounds/Voice4.ogg");
	//_sounds.load(Configuration::Sounds::Voice5, "Media/Sounds/Voice5.ogg");
	_sounds.load(Configuration::Sounds::Explosion, "Media/Sounds/Explosion.ogg");
}
