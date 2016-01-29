#pragma once

#include "ResourceManager.h"

class Player;
class Fruit;
class Configuration
{
public:
	Configuration(const Configuration&) = delete;
	Configuration & operator = (const Configuration&) = delete;

	Configuration() = delete;

	static ResourceManager<sf::Font, int> fonts_;
	enum Font
	{
		AIRSTRIKEB3D,
		AIRSTRIKEACAD
	};

	static ResourceManager<sf::Music, int> music_;
	enum Music : int
	{
		THEME
	};
	static ResourceManager<sf::Texture, int> textures_;
	enum Textures
	{
		GRASS,
		SHEEP,
		MINE,
		APPLE,
		PEAR,
		CHERRY,
		LIFE
	};

	static ResourceManager<sf::SoundBuffer, int> sounds_;
	enum Sounds
	{
		VOICE1,
		VOICE2,
		//Voice3,
		VOICE4,
		EXPLOSION,
		EAT_APPLE,
		EAT_CHERRY,
		EAT_PEAR
		//Voice5
	};

	static Player* player_;
	static Fruit* fruit_;
	static int max_speed_;
	static int player_lives_;

	static int score_;
	static sf::Text score_text_;

	static float timer_;
	static sf::Text timer_text_;

	static float voice_timer_;

	static float mine_timer_;
	static float mine_interval_;

	static std::vector<sf::Sprite> life_container_;

	static void IncreaseScore(int points);
	
	static void Draw(sf::RenderTarget & target);

	static void Initialize();

	static void InitializeTextures();
	static void InitializeMusic();
	static void InitializeSounds();
	static void InitializeFonts();
	static void InitializeTexts();
	static void InitializeLife();
	static sf::Clock clock_;

};

// random number generators, engine and distribution
static std::default_random_engine eng(Configuration::clock_.getElapsedTime().asMilliseconds());
static std::uniform_int_distribution<unsigned> random_0_1600(0, 1600);
static std::uniform_int_distribution<unsigned> random_0_900(0, 900);
static std::uniform_int_distribution<unsigned> random_0_2(0, 2);
static std::uniform_int_distribution<unsigned> random_8_14(8, 14);

