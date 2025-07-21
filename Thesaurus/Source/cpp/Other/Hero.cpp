#include "../../header/Hero.h"


Hero::Hero()
{
	HeroImages = new sf::Image[5];
	HeartImages = new sf::Image[10];
	HeroTextures = new sf::Texture[5];
	HeartTextures = new sf::Texture[10];

	HeroImages[0].loadFromFile("Game\\Texture\\Main character\\WALK_C.png");
	HeroImages[1].loadFromFile("Game\\Texture\\Main character\\RUN_C.png");
	HeroImages[2].loadFromFile("Game\\Texture\\Main character\\IDLE_C.png");
	HeroImages[3].loadFromFile("Game\\Texture\\Main character\\WALK_FIGHT_C.png");
	HeroImages[4].loadFromFile("Game\\Texture\\Main character\\RUN_FIGHT_C.png");

	for (int i = 0; i < 5; ++i) {
		HeroTextures[i].loadFromImage(HeroImages[i]);
	}

	HeroSprite.setTexture(HeroTextures[2]);
	HeroSprite.setTextureRect(sf::IntRect(0, 0, HeroRectSize.x, HeroRectSize.y));
	HeroSprite.setScale(sf::Vector2f(HeroSize.x / HeroRectSize.x, HeroSize.y / HeroRectSize.y));

	HeroCurrentRectSize = HeroRectSizeFight;
	HeroCurrentSize = HeroSize;

	HeartImages[0].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-0.5.png");
	HeartImages[1].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-1.png");
	HeartImages[2].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-1.5.png");
	HeartImages[3].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-2.png");
	HeartImages[4].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-2.5.png");
	HeartImages[5].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-3.png");
	HeartImages[6].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-3.5.png");
	HeartImages[7].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-4.png");
	HeartImages[8].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-4.5.png");
	HeartImages[9].loadFromFile("Game\\Texture\\Main character\\Hearts\\heart-5.png");

	for (int i = 0; i < 10; ++i) {
		HeartTextures[i].loadFromImage(HeartImages[i]);
	}

	HeartSprite.setTexture(HeartTextures[9]);
	HeartSprite.setScale(sf::Vector2f(40.f / 1291, 6.f / 193));
}

Hero::~Hero()
{
	if (HeroImages != nullptr) {
		delete[] HeroImages;
		HeroImages = nullptr;
	}
	if (HeroTextures != nullptr) {
		delete[] HeroTextures;
		HeroTextures = nullptr;
	}
	if (HeartImages != nullptr) {
		delete[] HeartImages;
		HeartImages = nullptr;
	}
	if (HeartTextures != nullptr) {
		delete[] HeartTextures;
		HeartTextures = nullptr;
	}
}

bool Hero::HeroMoveCollisionFunc(moveDirection direction, sf::FloatRect* StaticCollisionArr, int StaticCollisionSize,
	sf::FloatRect* DoorCollisionArr, int DoorCollisionSize,
	sf::FloatRect* SectionsCollisionArr, int SectionsCollisionSize)
{
	sf::FloatRect tempHeroPos = HeroSprite.getGlobalBounds();
	switch (direction) {
		case LEFT: tempHeroPos.left += (-1 * ((ANI_MODE == WALK) ? HeroWalkSpeed : HeroRunSpeed) * HeroMoveTime.asMilliseconds()); break;
		case RIGHT: tempHeroPos.left += (1 * ((ANI_MODE == WALK) ? HeroWalkSpeed : HeroRunSpeed) * HeroMoveTime.asMilliseconds()); break;
		case UP: tempHeroPos.top += (-1 * ((ANI_MODE == WALK) ? HeroWalkSpeed : HeroRunSpeed) * HeroMoveTime.asMilliseconds()); break;
		case DOWN: tempHeroPos.top += (1 * ((ANI_MODE == WALK) ? HeroWalkSpeed : HeroRunSpeed) * HeroMoveTime.asMilliseconds()); break;
	};
	for (int i = 0; i < StaticCollisionSize; ++i) {
		if (StaticCollisionArr[i].intersects(tempHeroPos)) {
			return false;
		}
	}
	for (int i = 0; i < DoorCollisionSize; ++i) {
		if (DoorCollisionArr[i].intersects(tempHeroPos)) {
			return false;
		}
	}
	for (int i = 0; i < SectionsCollisionSize; ++i) {
		if (SectionsCollisionArr[i].intersects(tempHeroPos)) {
			return false;
		}
	}
	if (NPCPosition.intersects(tempHeroPos)) {
		return false;
	}
	return true;
}

void Hero::HeroChangeMode()
{
	if (ANI_MODE == IDLE) {
		ANI_MODE = WALK;
		animationCurrentFrame = 0;
	}
	if (HeroModeTimer.asMilliseconds() > 2500 && ANI_MODE == WALK) {
		ANI_MODE = RUN;
		animationCurrentFrame = 0;
	}
}

void Hero::SetupCurrents()
{
	if (ANI_MODE == RUN) {
		HeroSprite.setTexture(HeroTextures[(HeroFight) ? 4 : 1]);
		CurrentMaxFrame = (HeroFight) ? 6 : 7;
		CurrentAniOneFrameTime = (HeroFight) ? aniOneFrameTimeRUN_FIGHT : aniOneFrameTimeRUN;
	}
	else if (ANI_MODE == WALK) {
		HeroSprite.setTexture(HeroTextures[(HeroFight ? 3 : 0)]);
		CurrentMaxFrame = (HeroFight) ? 5 : 8;
		CurrentAniOneFrameTime = (HeroFight) ? aniOneFrameTimeWALK_FIGHT : aniOneFrameTimeWALK;
	}
	HeroCurrentRectSize = (HeroFight) ? HeroRectSizeFight : HeroRectSize;
	HeroCurrentSize = (HeroFight) ? HeroSizeFight : HeroSize;
}

void Hero::HeroMove(int direction, sf::FloatRect* StaticCollisionArr, int StaticCollisionSize,
	sf::FloatRect* DoorCollisionArr, int DoorCollisionSize,
	sf::FloatRect* SectionsCollisionArr, int SectionsCollisionSize, sf::Sound*& PlaySounds)
{
	moveDirection tempDir;
	switch (direction) {
		case 1: tempDir = LEFT; break;
		case 2: tempDir = RIGHT; break;
		case 3: tempDir = UP; break;
		case 4: tempDir = DOWN; break;
	};


	HeroChangeMode();
	HeroAnimationTimer += HeroMoveTime;
	HeroModeTimer += HeroMoveTime;
	HeroMoveCollision = HeroMoveCollisionFunc(tempDir, StaticCollisionArr, StaticCollisionSize,
		DoorCollisionArr, DoorCollisionSize,
		SectionsCollisionArr, SectionsCollisionSize);
	
	SetupCurrents();

	if (HeroMoveCollision) {
		if (PlaySounds[0].getStatus() != sf::Sound::Status::Playing) {
			PlaySounds[0].play();
		}
	}
	//else {
	//	if (PlaySounds[1].getStatus() != sf::Sound::Status::Playing) {
	//		PlaySounds[1].play();
	//	}
	//}

	if (MOVE_DIR != tempDir) {
		MOVE_DIR = tempDir;
		animationCurrentFrame = 0;
		HeroAnimationTimer = sf::Time::Zero;
		HeroSprite.setTextureRect(sf::IntRect(((tempDir == LEFT) ? HeroCurrentRectSize.x : 0), 0, ((tempDir == LEFT) ? -HeroCurrentRectSize.x : HeroCurrentRectSize.x), HeroCurrentRectSize.y));
	}
	if (HeroAnimationTimer.asMilliseconds() > CurrentAniOneFrameTime) {
		HeroAnimationTimer = sf::Time::Zero;
		animationCurrentFrame++;
		animationCurrentFrame = (animationCurrentFrame < CurrentMaxFrame) ? animationCurrentFrame : 0;
		HeroSprite.setTextureRect(sf::IntRect(((tempDir == LEFT) ? HeroCurrentRectSize.x : 0) + (animationCurrentFrame * HeroCurrentRectSize.x), 0, ((tempDir == LEFT) ? -HeroCurrentRectSize.x : HeroCurrentRectSize.x), HeroCurrentRectSize.y));
	}
	switch (tempDir) {
		case LEFT: HeroSprite.move(-1 * ((ANI_MODE == WALK) ? HeroWalkSpeed : HeroRunSpeed) * HeroMoveTime.asMilliseconds() * (int)HeroMoveCollision, 0.f); break;
		case RIGHT: HeroSprite.move(1 * ((ANI_MODE == WALK) ? HeroWalkSpeed : HeroRunSpeed) * HeroMoveTime.asMilliseconds() * (int)HeroMoveCollision, 0.f); break;
		case UP: HeroSprite.move(0.f, -1 * ((ANI_MODE == WALK) ? HeroWalkSpeed : HeroRunSpeed) * HeroMoveTime.asMilliseconds() * (int)HeroMoveCollision); break;
		case DOWN: HeroSprite.move(0.f, 1 * ((ANI_MODE == WALK) ? HeroWalkSpeed : HeroRunSpeed) * HeroMoveTime.asMilliseconds() * (int)HeroMoveCollision);  break;
	};
}

void Hero::HeroStand()
{
	if (HeroFight) {
		HeroSprite.setTexture(HeroTextures[3]);
		HeroAnimationTimer += HeroMoveTime;
		if (HeroAnimationTimer.asMilliseconds() > aniOneFrameTimeWALK_FIGHT) {
			HeroAnimationTimer = sf::Time::Zero;
			animationCurrentFrame++;
			animationCurrentFrame = (animationCurrentFrame < aniMaxFrameWALK_FIGHT) ? animationCurrentFrame : 0;
			HeroSprite.setTextureRect(sf::IntRect(0 + (animationCurrentFrame * HeroRectSizeFight.x), 0, HeroRectSizeFight.x, HeroRectSizeFight.y));
		}
	}
	else {
		MOVE_DIR = STAND;
		ANI_MODE = IDLE;
		HeroAnimationTimer = sf::Time::Zero;
		HeroModeTimer = sf::Time::Zero;
		animationCurrentFrame = 0;
		HeroSprite.setTexture(HeroTextures[2]);
		HeroSprite.setTextureRect(sf::IntRect(0, 0, HeroRectSize.x, HeroRectSize.y));
	}
}

void Hero::HeroDisplaier(sf::RenderWindow& MainWin)
{
	if (HeroHeart > 0 && HeroHeart < 1) {
		HeartSprite.setTexture(HeartTextures[0]);
	}
	else if (HeroHeart > 1 && HeroHeart < 5) {
		HeartSprite.setTexture(HeartTextures[(int)(HeroHeart * 2) - 1]);
	}
	else if (HeroHeart == 5) {
		HeartSprite.setTexture(HeartTextures[9]);
	}
	HeartSprite.setPosition(sf::Vector2f(HeroSprite.getGlobalBounds().left - 4, HeroSprite.getGlobalBounds().top - 9));

	MainWin.draw(HeroSprite);
	MainWin.draw(HeartSprite);
}

float Hero::HeroFightFunc(sf::FloatRect NPCPostion)
{
	if (NPCPostion.intersects(HeroSprite.getGlobalBounds()) && HeroFight) {
		HeroFightTime = HeroMoveTime;
		return (HeroFightTime.asMilliseconds() * HeroDamage);
	}
	return 0.f;
}

void Hero::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		IOFile << HeroSprite.getGlobalBounds().left << "\n" <<
			HeroSprite.getGlobalBounds().top << "\n" <<
			HeroSprite.getGlobalBounds().width << "\n" <<
			HeroSprite.getGlobalBounds().height << std::endl;
		IOFile << HeroCurrentRectSize.x << "\n" <<
			HeroCurrentRectSize.y << std::endl;
		IOFile << HeroCurrentSize.x << "\n" <<
			HeroCurrentSize.y << std::endl;
		IOFile << ANI_MODE << std::endl;
		IOFile << MOVE_DIR << std::endl;
		IOFile << HeroModeTimer.asMilliseconds() << std::endl;
		IOFile << HeroMoveTime.asMilliseconds() << std::endl;
		IOFile << HeroAnimationTimer.asMilliseconds() << std::endl;
		IOFile << CurrentMaxFrame << std::endl;
		IOFile << CurrentAniOneFrameTime << std::endl;
		IOFile << HeroFightTime.asMilliseconds() << std::endl;
		IOFile << NPCPosition.left << "\n" << NPCPosition.top << "\n" <<
			NPCPosition.width << "\n" << NPCPosition.height << std::endl;
		IOFile << HeroMoveCollision << std::endl;
		IOFile << HeroKeysAmount << std::endl;
		IOFile << HeroRelic << std::endl;
		IOFile << HeroFight << std::endl;
		IOFile << HeroHeart << std::endl;
	}
	IOFile.close();
}

void Hero::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		sf::FloatRect tempHeroPos;
		while (getline(IOFile, temp)) {
			switch (counter) {
				case 0: tempHeroPos.left = std::stof(temp); break;
				case 1: tempHeroPos.top = std::stof(temp); break;
				case 2: tempHeroPos.width = std::stof(temp); break;
				case 3: tempHeroPos.height = std::stof(temp); break;
				case 4: HeroCurrentRectSize.x = std::stof(temp); break;
				case 5: HeroCurrentRectSize.y = std::stof(temp); break;
				case 6: HeroCurrentSize.x = std::stof(temp); break;
				case 7: HeroCurrentSize.y = std::stof(temp); break;
				case 8: ANI_MODE = (animationMode)std::stof(temp); break;
				case 9: MOVE_DIR = (moveDirection)std::stof(temp); break;
				case 10: HeroModeTimer = sf::milliseconds(std::stof(temp)); break;
				case 11: HeroMoveTime = sf::milliseconds(std::stof(temp)); break;
				case 12: HeroAnimationTimer = sf::milliseconds(std::stof(temp)); break;
				case 13: CurrentMaxFrame = std::stof(temp);  break;
				case 14: CurrentAniOneFrameTime = std::stof(temp); break;
				case 15: HeroFightTime = sf::milliseconds(std::stof(temp)); break;
				case 16: NPCPosition.left = std::stof(temp); break;
				case 17: NPCPosition.top = std::stof(temp); break;
				case 18: NPCPosition.width = std::stof(temp); break;
				case 19: NPCPosition.height = std::stof(temp); break;
				case 20: HeroMoveCollision = std::stof(temp); break;
				case 21: HeroKeysAmount = std::stof(temp); break;
				case 22: HeroRelic = std::stof(temp); break;
				case 23: HeroFight = std::stof(temp); break;
				case 24: HeroHeart = std::stof(temp); break;
			};
			counter++;
		}
		HeroSprite.setPosition(tempHeroPos.left, tempHeroPos.top);
	}
	IOFile.close();
}