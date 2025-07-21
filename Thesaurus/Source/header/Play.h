#pragma once
#include <SFML\Audio.hpp>
#include "Hero.h"
#include "Map.h"
#include "Camera.h"
#include "Keys.h"
#include "Password.h"
#include "MapHider.h"
#include "RelicShower.h"
#include "Helper.h"
#include "NPC.h"
#include <fstream>

namespace fs = std::filesystem;

enum MapEnum {
	START,
	GAME_MAP,
	CHESS
};

struct PlayPos {
	sf::FloatRect* ObjectsArray = nullptr;
	int ArraySize;
};

class Play
{
public:
	bool DYNAMIC = false;

	sf::Image EscImage;
	sf::Texture EscTexture;
	sf::Sprite EscSprite;

	Hero* PlayHero = nullptr;
	Map* PlayMaps[3];
	
	Camera* PlayCamera = nullptr;
	MapEnum CurrentMap = START;

	int SectionsAmount = 7;

	PlayPos* StaticCollision = nullptr;
	PlayPos* TempCollision = nullptr;
	sf::FloatRect* CasesPositions = nullptr;
	bool CasesStates[7];
	RelicShower* ShowRelicObject = nullptr;;
	Helper* HelperObject = nullptr;

	Keys* MapKeysArr[7];
	int CurrentSection = 0;

	Password* PlayPassword = nullptr;
	bool PasswordWinOpened = false;
	MapHider* MapHiderObject = nullptr;

	NPC* PlayNPC = nullptr;
	bool PlayFight = false;
	bool BetweenFightAndRelic = false;
	PlayPos* NPCStaticPositions = nullptr;

	sf::SoundBuffer* PlaySoundBuffer = nullptr;
	sf::Sound* PlaySounds = nullptr;

	Play();
	~Play();

	void PlayDisplaier(sf::RenderWindow&);
	bool PlayController(sf::RenderWindow&);
	void PlayUpdater(sf::Clock&, float);
	void PlayFightFunc(sf::Clock&);

	// Useful
	sf::FloatRect* FitArr(sf::FloatRect*, int);
	void DeleteArrElement(auto*&, int&, int);
	void FillKeysAreaArray(sf::FloatRect, sf::FloatRect*, int&);

	// Save
	std::string SavePath = "Backup\\Play.save";
	std::fstream IOFile;
	void Save();
	void Pull();

	// Hero Dead
	void HeroDeadShower(sf::RenderWindow&);
	bool HeroDeadBoolean = false;
	float ShowDeadMessageTime = 2000.f;
	sf::Time DeadTime = sf::Time::Zero;
	sf::RectangleShape HiderShape;
	sf::Font TextFont;
	sf::Text DeadText;

};