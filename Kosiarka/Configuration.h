#pragma once

#include "ResourceManager.h"

//#include "Random.h"
class Player;
class Configuration
{
public:
	Configuration(const Configuration&) = delete;
	Configuration & operator = (const Configuration&) = delete;

	Configuration() = delete;


	static ResourceManager<sf::Music, int> _music;
	enum Music : int
	{
		Theme
	};
	static ResourceManager<sf::Texture, int> _textures;
	enum Textures
	{
		Grass,
		Sheep,
		Mine,
		Fruit1,
		Fruit2,
		Fruit3
	};

	static ResourceManager<sf::SoundBuffer, int> _sounds;
	enum Sounds
	{
		Voice1,
		Voice2,
		//Voice3,
		Voice4,
		Explosion
		//Voice5
	};

	static Player* player;
	static int MAX_SPEED;

	static float _voice_timer;

	static float _mine_timer;
	static float _mine_interval;

	
	static void initialize();

	static void initTextures();
	static void initMusic();
	static void initSounds();
	static sf::Clock clock;

};

// random number generators, engine and distribution
static std::default_random_engine eng(Configuration::clock.getElapsedTime().asMilliseconds());
static std::uniform_int_distribution<unsigned> res_1600(0, 1600); // for voice distribution
static std::uniform_int_distribution<unsigned> res_900(0, 900);
static std::uniform_int_distribution<unsigned> random_0_2(0, 2);
static std::uniform_int_distribution<unsigned> random_8_14(8, 14);

