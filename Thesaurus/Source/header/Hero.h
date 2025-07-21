#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

enum animationMode {
	IDLE,
	WALK,
	RUN
};

enum moveDirection {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STAND
};

class Hero
{
public:
	sf::Sprite HeroSprite;
	sf::Image* HeroImages = nullptr;
	sf::Image* HeartImages = nullptr;
	sf::Texture* HeroTextures = nullptr;
	sf::Texture* HeartTextures = nullptr;
	sf::Sprite HeartSprite;

	// Rect sizes
	sf::Vector2f HeroRectSize = sf::Vector2f(70.f, 67.f);
	sf::Vector2f HeroRectSizeFight = sf::Vector2f(70.f, 77.f);
	sf::Vector2f HeroCurrentRectSize;

	sf::Vector2f HeroSize = sf::Vector2f(32.f, 30.62f);
	sf::Vector2f HeroSizeFight = sf::Vector2f(32.f, 35.2f);
	sf::Vector2f HeroCurrentSize;

	// Moving mode
	animationMode ANI_MODE = IDLE;
	sf::Time HeroModeTimer;

	// Moving
	moveDirection MOVE_DIR = STAND;
	sf::Time HeroMoveTime = sf::Time::Zero;
	float HeroWalkSpeed = 50.f / 1000;
	float HeroRunSpeed = 15.f / 100;

	// Animation
	sf::Time HeroAnimationTimer = sf::Time::Zero;
	int aniMaxFrameWALK = 8;
	int aniMaxFrameRUN = 7;
	int aniMaxFrameRUN_FIGHT = 6;
	int aniMaxFrameWALK_FIGHT = 5;
	int CurrentMaxFrame;

	int animationCurrentFrame = 0;
	float maxAnimationTime = 1000.f;

	float aniOneFrameTimeWALK = maxAnimationTime / aniMaxFrameWALK;
	float aniOneFrameTimeRUN = maxAnimationTime / aniMaxFrameRUN;
	float aniOneFrameTimeRUN_FIGHT = maxAnimationTime / aniMaxFrameRUN_FIGHT;
	float aniOneFrameTimeWALK_FIGHT = maxAnimationTime / aniMaxFrameWALK_FIGHT;
	float CurrentAniOneFrameTime;

	Hero();
	~Hero();

	// Base Func
	void HeroMove(int, sf::FloatRect*, int, sf::FloatRect*, int, sf::FloatRect*, int, sf::Sound*&);
	void HeroStand();
	void HeroChangeMode();
	void SetupCurrents();
	void HeroDisplaier(sf::RenderWindow&);

	// Fight
	float HeroFightFunc(sf::FloatRect NPCPostion);
	float HeroDamage = 0.8f / 1000.f;
	sf::Time HeroFightTime = sf::Time::Zero;
	sf::FloatRect NPCPosition = sf::FloatRect(0,0,0,0);

	// Collision
	bool HeroMoveCollision = true;
	bool HeroMoveCollisionFunc(moveDirection, sf::FloatRect*, int, sf::FloatRect*, int, sf::FloatRect*, int);

	// Keys
	int HeroKeysAmount = 0;

	// Relic
	bool HeroRelic = false;

	// Fight
	bool HeroFight = false;

	// Hearts
	float HeroHeart = 5.f;

	// Saver
	std::string SavePath = "Backup\\Hero.save";
	std::fstream IOFile;
	void Save();
	void Pull();
};