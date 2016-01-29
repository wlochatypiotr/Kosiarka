#include "stdafx.h"
#include "Configuration.h"
#include "Random.h"
#include "Collision.h"

// Resource Managers
ResourceManager<sf::Texture, int> Configuration::textures_;
ResourceManager<sf::Music, int> Configuration::music_;
ResourceManager<sf::SoundBuffer, int> Configuration::sounds_;
ResourceManager<sf::Font, int> Configuration::fonts_;


Player* Configuration::player_ = nullptr;

//defines game difficulty

int Configuration::max_speed_;
int Configuration::player_lives_ = 3;

//keeps track of score
int Configuration::score_ = 0;
sf::Text Configuration::score_text_;

//keeps track of player's time
float Configuration::timer_;
sf::Text Configuration::timer_text_;

//stores interval between sheep's voice
float Configuration::voice_timer_;

//defines mine spwaning timing
float Configuration::mine_timer_;
float Configuration::mine_interval_ = 5;

//defines fruit spawning timing 
float Configuration::fruit_timer_;
float Configuration::fruit_interval_ = 3;

sf::Clock Configuration::clock_;



void Configuration::IncreaseScore(int points)
{
	score_ += points;
}

void Configuration::Initialize()
{
	max_speed_ = 300;
	InitializeTextures();
	InitializeSounds();
	InitializeMusic();
	InitializeFonts();
	InitializeTexts();


	music_.get(Configuration::Music::THEME).setLoop(true);
	music_.get(Configuration::Music::THEME).play();
}


void Configuration::InitializeTextures()
{
	textures_.load(APPLE, "Media/Textures/apple.png");
	textures_.load(PEAR, "Media/Textures/pear.png");
	textures_.load(CHERRY, "Media/Textures/cherry.png");
	textures_.load(SHEEP, "Media/Textures/Sheep.png");
	textures_.load(GRASS, "media/Textures/Grass.jpg");
	textures_.load(MINE, "Media/Textures/Mine.png");	
}

void Configuration::InitializeMusic()
{
	music_.load(THEME, "media/Sounds/Cipher2.ogg");
}

void Configuration::InitializeSounds()
{
	sounds_.load(Configuration::Sounds::VOICE1, "Media/Sounds/Voice1.ogg");
	sounds_.load(Configuration::Sounds::VOICE2, "Media/Sounds/Voice2.ogg");
	//_sounds.load(Configuration::Sounds::Voice3, "Media/Sounds/Voice3.ogg");
	sounds_.load(Configuration::Sounds::VOICE4, "Media/Sounds/Voice4.ogg");
	//_sounds.load(Configuration::Sounds::Voice5, "Media/Sounds/Voice5.ogg");
	sounds_.load(Configuration::Sounds::EXPLOSION, "Media/Sounds/Explosion.ogg");
}

void Configuration::InitializeFonts()
{
	fonts_.load(Configuration::Font::AIRSTRIKEB3D, "Media/Fonts/airstrikeb3d.ttf");
	fonts_.load(Configuration::Font::AIRSTRIKEACAD, "Media/Fonts/airstrikeacad.ttf");
}

void Configuration::InitializeTexts()
{
	//Score display
	score_text_.setFont(Configuration::fonts_.get(AIRSTRIKEACAD));
	score_text_.setCharacterSize(50);
	score_text_.setColor(sf::Color::Black);
	score_text_.setPosition(sf::Vector2f(20, 5));

	//Timer display
	timer_text_.setFont(Configuration::fonts_.get(AIRSTRIKEACAD));
	timer_text_.setCharacterSize(40);
	timer_text_.setColor(sf::Color::White);
	timer_text_.setPosition(sf::Vector2f(20, 50));
}
