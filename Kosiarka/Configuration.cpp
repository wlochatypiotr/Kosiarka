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
Entity* Configuration::fruit_ = nullptr;

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

//defines mine spawning timing
float Configuration::mine_timer_;
float Configuration::mine_interval_ = 5;

//defines fruit spawning timing 
float Configuration::fruit_timer_;
float Configuration::fruit_interval_ = 3;

std::vector<sf::Sprite> Configuration::life_container_;

sf::Clock Configuration::clock_;



void Configuration::IncreaseScore(int points)
{
	score_ += points;
}

void Configuration::Draw(sf::RenderTarget & target)
{
	target.draw(score_text_);
	target.draw(timer_text_);
	if (player_lives_ > 0)
	{
		for (int i = 0; i != player_lives_; ++i)
			target.draw(life_container_[i]);
	}
}

bool Configuration::IsGameOver()
{
	return player_lives_ < 0;
}

void Configuration::Initialize()
{
	max_speed_ = 300;
	InitializeTextures();
	InitializeSounds();
	InitializeMusic();
	InitializeFonts();
	InitializeTexts();

	InitializeLife();

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
	textures_.load(LIFE, "Media/Textures/Life.png");
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
	sounds_.load(Configuration::Sounds::EAT_APPLE, "Media/Sounds/Apple.ogg");
	sounds_.load(Configuration::Sounds::EAT_PEAR, "Media/Sounds/Pear.wav");
	sounds_.load(Configuration::Sounds::EAT_CHERRY, "Media/Sounds/Cherry.ogg");

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

void Configuration::InitializeLife()
{
	sf::Sprite life1(Configuration::textures_.get(LIFE));
	sf::Sprite life2(Configuration::textures_.get(LIFE));
	sf::Sprite life3(Configuration::textures_.get(LIFE));

	life1.setPosition(1540, 20);
	life2.setPosition(1500, 20);
	life3.setPosition(1460, 20);

	Configuration::life_container_.push_back(std::move(life1));
	Configuration::life_container_.push_back(std::move(life2));
	Configuration::life_container_.push_back(std::move(life3));
}

void Configuration::Reset()
{
	player_lives_ = 3;
	score_ = 0;
	score_text_.setString("Score: 0");
}
