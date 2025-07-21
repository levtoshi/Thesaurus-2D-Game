#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

enum NPCanimationMode {
	IDLE_NPC,
	WALK_NPC,
	RUN_NPC
};

enum NPCmoveDirection {
	LEFT_NPC,
	RIGHT_NPC
};

class NPC
{
public:
	
	sf::Sprite NPCSprite;
	sf::Image* NPCImages = nullptr;
	sf::Image* HeartImages = nullptr;
	sf::Texture* NPCTextures = nullptr;
	sf::Texture* HeartTextures = nullptr;
	sf::Sprite HeartSprite;

	// Rect sizes
	sf::Vector2f NPCRectSize = sf::Vector2f(70.f, 67.f);
	sf::Vector2f NPCRectSizeFight = sf::Vector2f(70.f, 77.f);
	sf::Vector2f NPCCurrentRectSize;

	sf::Vector2f NPCSize = sf::Vector2f(32.f, 30.62f);
	sf::Vector2f NPCSizeFight = sf::Vector2f(32.f, 35.2f);
	sf::Vector2f NPCCurrentSize;
	

	// Moving
	NPCmoveDirection MOVE_DIR = RIGHT_NPC;
	sf::Time NPCMainTime = sf::Time::Zero;
	float NPCWalkSpeed = 20.f / 1000;//40
	float NPCRunSpeed = 6.f / 100;//12

	// Animation
	NPCanimationMode ANI_MODE = IDLE_NPC;
	sf::Time NPCModeTimer;

	sf::Time NPCAnimationTimer = sf::Time::Zero;
	int NPCaniMaxFrameWALK = 8;
	int NPCaniMaxFrameRUN = 7;
	int NPCaniMaxFrameRUN_FIGHT = 6;
	int NPCaniMaxFrameWALK_FIGHT = 5;
	int CurrentMaxFrame;

	int NPCanimationCurrentFrame = 0;
	float NPCmaxAnimationTime = 1000.f;

	float NPCaniOneFrameTimeWALK = NPCmaxAnimationTime / NPCaniMaxFrameWALK;
	float NPCaniOneFrameTimeRUN = NPCmaxAnimationTime / NPCaniMaxFrameRUN;
	float NPCaniOneFrameTimeRUN_FIGHT = NPCmaxAnimationTime / NPCaniMaxFrameRUN_FIGHT;
	float NPCaniOneFrameTimeWALK_FIGHT = NPCmaxAnimationTime / NPCaniMaxFrameWALK_FIGHT;
	float CurrentAniOneFrameTime;

	// Fight
	sf::FloatRect NPCCurrentPos;
	bool NPCFight = false;
	float NPCHeart = 5.f;
	int VectorBuggingScale = 12;
	float NPCDamage = 0.4f / 1000.f;
	sf::Time NPCFightTime = sf::Time::Zero;

	NPC();
	~NPC();

	void NPCDisplaier(sf::RenderWindow&);
	void NPCMove(sf::FloatRect HeroFightPos, sf::FloatRect HeroCollisionPos, sf::FloatRect* StaticCollisionArr, int StaticCollisionSize,
		sf::FloatRect* DoorCollisionArr, int DoorCollisionSize,
		sf::FloatRect* SectionsCollisionArr, int SectionsCollisionSize);
	void NPCChangeMode();
	void NPCSetupCurrents();
	float NPCFightFunc();

	// Colision
	bool NPCMoveCollision = true;
	bool NPCMoveCollisionFunc(sf::Vector2f nextVector, sf::FloatRect* StaticCollisionArr, int StaticCollisionSize,
		sf::FloatRect* DoorCollisionArr, int DoorCollisionSize,
		sf::FloatRect* SectionsCollisionArr, int SectionsCollisionSize);

	// Save
	std::string SavePath = "Backup\\NPC.save";
	std::fstream IOFile;
	void Save();
	void Pull();
};