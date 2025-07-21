#include "../../header/NPC.h"

NPC::NPC()
{
	NPCImages = new sf::Image[5];
	HeartImages = new sf::Image[10];
	NPCTextures = new sf::Texture[5];
	HeartTextures = new sf::Texture[10];

	NPCImages[0].loadFromFile("Game\\Texture\\NPC\\WALK_C.png");
	NPCImages[1].loadFromFile("Game\\Texture\\NPC\\RUN_C.png");
	NPCImages[2].loadFromFile("Game\\Texture\\NPC\\IDLE_C.png");
	NPCImages[3].loadFromFile("Game\\Texture\\NPC\\WALK_FIGHT_C.png");
	NPCImages[4].loadFromFile("Game\\Texture\\NPC\\RUN_FIGHT_C.png");

	for (int i = 0; i < 5; ++i) {
		NPCTextures[i].loadFromImage(NPCImages[i]);
	}

	NPCSprite.setTexture(NPCTextures[2]);
	NPCSprite.setTextureRect(sf::IntRect(0, 0, NPCRectSize.x, NPCRectSize.y));
	NPCSprite.setScale(sf::Vector2f(NPCSize.x / NPCRectSize.x, NPCSize.y / NPCRectSize.y));

	NPCCurrentRectSize = NPCRectSizeFight;
	NPCCurrentSize = NPCSize;

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

NPC::~NPC()
{
	if (NPCImages != nullptr) {
		delete[] NPCImages;
		NPCImages = nullptr;
	}
	if (NPCTextures != nullptr) {
		delete[] NPCTextures;
		NPCTextures = nullptr;
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

bool NPC::NPCMoveCollisionFunc(sf::Vector2f nextVector, sf::FloatRect* StaticCollisionArr, int StaticCollisionSize,
	sf::FloatRect* DoorCollisionArr, int DoorCollisionSize,
	sf::FloatRect* SectionsCollisionArr, int SectionsCollisionSize)
{
	sf::FloatRect nextPos = sf::FloatRect(NPCCurrentPos.left + ((nextVector.x < 0 ? -1 : 1) * ((ANI_MODE == WALK_NPC) ? NPCWalkSpeed : NPCRunSpeed) * NPCMainTime.asMilliseconds()),
		NPCCurrentPos.top + ((nextVector.y < 0 ? -1 : 1) * ((ANI_MODE == WALK_NPC) ? NPCWalkSpeed : NPCRunSpeed) * NPCMainTime.asMilliseconds()), NPCSize.x, NPCSize.y);
	for (int i = 0; i < StaticCollisionSize; ++i) {
		if (StaticCollisionArr[i].intersects(nextPos)) {
			return false;
		}
	}
	for (int i = 0; i < DoorCollisionSize; ++i) {
		if (DoorCollisionArr[i].intersects(nextPos)) {
			return false;
		}
	}
	for (int i = 0; i < SectionsCollisionSize; ++i) {
		if (SectionsCollisionArr[i].intersects(nextPos)) {
			return false;
		}
	}
	return true;
}

void NPC::NPCChangeMode()
{
	if (ANI_MODE == IDLE_NPC) {
		ANI_MODE = WALK_NPC;
		NPCanimationCurrentFrame = 0;
	}
	if (NPCModeTimer.asMilliseconds() > 2500 && ANI_MODE == WALK_NPC && !NPCFight) {
		ANI_MODE = RUN_NPC;
		NPCanimationCurrentFrame = 0;
	}
}

void NPC::NPCSetupCurrents()
{
	if (ANI_MODE == RUN_NPC) {
		NPCSprite.setTexture(NPCTextures[(NPCFight) ? 4 : 1]);
		CurrentMaxFrame = (NPCFight) ? 6 : 7;
		CurrentAniOneFrameTime = (NPCFight) ? NPCaniOneFrameTimeRUN_FIGHT : NPCaniOneFrameTimeRUN;
	}
	else if (ANI_MODE == WALK_NPC) {
		NPCSprite.setTexture(NPCTextures[(NPCFight ? 3 : 0)]);
		CurrentMaxFrame = (NPCFight) ? 5 : 8;
		CurrentAniOneFrameTime = (NPCFight) ? NPCaniOneFrameTimeWALK_FIGHT : NPCaniOneFrameTimeWALK;
	}
	NPCCurrentRectSize = (NPCFight) ? NPCRectSizeFight : NPCRectSize;
	NPCCurrentSize = (NPCFight) ? NPCSizeFight : NPCSize;
}

void NPC::NPCMove(sf::FloatRect HeroFightPos, sf::FloatRect HeroCollisionPos, sf::FloatRect* StaticCollisionArr, int StaticCollisionSize,
	sf::FloatRect* DoorCollisionArr, int DoorCollisionSize,
	sf::FloatRect* SectionsCollisionArr, int SectionsCollisionSize)
{
	NPCAnimationTimer += NPCMainTime;
	NPCModeTimer += NPCMainTime;

	if (NPCCurrentPos.intersects(HeroFightPos)) {
		if (!NPCFight) {
			NPCFight = true;
			ANI_MODE == WALK_NPC;
		}
	}
	else {
		NPCFight = false;
	}

	NPCmoveDirection tempDir;
	sf::Vector2f MoveVector = sf::Vector2f(((HeroCollisionPos.left + HeroCollisionPos.width) < NPCCurrentPos.left ? HeroCollisionPos.left + HeroCollisionPos.width - NPCCurrentPos.left : HeroCollisionPos.left - (NPCCurrentPos.left + NPCCurrentPos.width)),
		(HeroCollisionPos.top + HeroCollisionPos.height) < NPCCurrentPos.top ? HeroCollisionPos.top + HeroCollisionPos.height - NPCCurrentPos.top : HeroCollisionPos.top - (NPCCurrentPos.top + NPCCurrentPos.height));

	if (MoveVector.x < VectorBuggingScale && MoveVector.x > -VectorBuggingScale) {
		tempDir = RIGHT_NPC;
	}
	else if (MoveVector.x < -VectorBuggingScale) {
		tempDir = LEFT_NPC;
	}
	else {
		tempDir = RIGHT_NPC;
	}
	int tempX = (MoveVector.x < 0 ? -1 : 1);
	int tempY = (MoveVector.y < 0 ? -1 : 1);
	if (MoveVector.x < VectorBuggingScale && MoveVector.x > -VectorBuggingScale) {
		tempX = 0;
	}
	if (MoveVector.y < VectorBuggingScale && MoveVector.y > -VectorBuggingScale) {
		tempY = 0;
	}

	NPCChangeMode();
	NPCMoveCollision = NPCMoveCollisionFunc(MoveVector,
		StaticCollisionArr, StaticCollisionSize,
		DoorCollisionArr, DoorCollisionSize,
		SectionsCollisionArr, SectionsCollisionSize);
	NPCSetupCurrents();


	if (MOVE_DIR != tempDir) {
		MOVE_DIR = tempDir;
		NPCanimationCurrentFrame = 0;
		NPCAnimationTimer = sf::Time::Zero;
		NPCSprite.setTextureRect(sf::IntRect(((tempDir == LEFT_NPC) ? NPCCurrentRectSize.x : 0), 0, ((tempDir == LEFT_NPC) ? -NPCCurrentRectSize.x : NPCCurrentRectSize.x), NPCCurrentRectSize.y));
	}
	if (NPCAnimationTimer.asMilliseconds() > CurrentAniOneFrameTime) {
		NPCAnimationTimer = sf::Time::Zero;
		NPCanimationCurrentFrame++;
		NPCanimationCurrentFrame = (NPCanimationCurrentFrame < CurrentMaxFrame) ? NPCanimationCurrentFrame : 0;
		NPCSprite.setTextureRect(sf::IntRect(((tempDir == LEFT_NPC) ? NPCCurrentRectSize.x : 0) + (NPCanimationCurrentFrame * NPCCurrentRectSize.x), 0, ((tempDir == LEFT_NPC) ? -NPCCurrentRectSize.x : NPCCurrentRectSize.x), NPCCurrentRectSize.y));
	}
	NPCSprite.move(tempX * ((ANI_MODE == WALK_NPC) ? NPCWalkSpeed : NPCRunSpeed) * NPCMainTime.asMilliseconds() * (int)NPCMoveCollision,
		tempY * ((ANI_MODE == WALK_NPC) ? NPCWalkSpeed : NPCRunSpeed) * NPCMainTime.asMilliseconds() * (int)NPCMoveCollision);
	NPCCurrentPos.left += tempX * ((ANI_MODE == WALK_NPC) ? NPCWalkSpeed : NPCRunSpeed) * NPCMainTime.asMilliseconds() * (int)NPCMoveCollision;
	NPCCurrentPos.top += tempY * ((ANI_MODE == WALK_NPC) ? NPCWalkSpeed : NPCRunSpeed) * NPCMainTime.asMilliseconds() * (int)NPCMoveCollision;
}


float NPC::NPCFightFunc()
{
	if (NPCFight) {
		NPCFightTime = NPCMainTime;
		return (NPCFightTime.asMilliseconds() * NPCDamage);
	}
	return 0;
}

void NPC::NPCDisplaier(sf::RenderWindow& MainWin)
{
	if (NPCHeart > 0 && NPCHeart < 1) {
		HeartSprite.setTexture(HeartTextures[0]);
	}
	else if (NPCHeart > 1 && NPCHeart < 5) {
		HeartSprite.setTexture(HeartTextures[(int)(NPCHeart * 2) - 1]);
	}
	else if (NPCHeart == 5) {
		HeartSprite.setTexture(HeartTextures[9]);
	}
	HeartSprite.setPosition(sf::Vector2f(NPCSprite.getGlobalBounds().left - 4, NPCSprite.getGlobalBounds().top - 9));

	MainWin.draw(HeartSprite);
	MainWin.draw(NPCSprite);
}

void NPC::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		IOFile << NPCCurrentRectSize.x << "\n" << NPCCurrentRectSize.y << std::endl;
		IOFile << NPCCurrentSize.x << "\n" << NPCCurrentSize.y << std::endl;
		IOFile << (int)MOVE_DIR << std::endl;
		IOFile << (int)ANI_MODE << std::endl;
		IOFile << CurrentMaxFrame << std::endl;
		IOFile << CurrentAniOneFrameTime << std::endl;
		IOFile << NPCCurrentPos.left << "\n" << NPCCurrentPos.top << "\n" << NPCCurrentPos.width << "\n" << NPCCurrentPos.height << std::endl;
		IOFile << (int)NPCFight << std::endl;
		IOFile << NPCHeart << std::endl;
	}
	IOFile.close();
}

void NPC::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		while (getline(IOFile, temp)) {
			switch (counter) {
				case 0: NPCCurrentRectSize.x = std::stof(temp); break;
				case 1: NPCCurrentRectSize.y = std::stof(temp); break;
				case 2: NPCCurrentSize.x = std::stof(temp); break;
				case 3: NPCCurrentSize.y = std::stof(temp); break;
				case 4: MOVE_DIR = (NPCmoveDirection)std::stof(temp); break;
				case 5: ANI_MODE = (NPCanimationMode)std::stof(temp); break;
				case 6: CurrentMaxFrame = std::stof(temp); break;
				case 7: CurrentAniOneFrameTime = std::stof(temp); break;
				case 8: NPCCurrentPos.left = std::stof(temp); break;
				case 9: NPCCurrentPos.top = std::stof(temp); break;
				case 10: NPCCurrentPos.width = std::stof(temp); break;
				case 11: NPCCurrentPos.height = std::stof(temp); break;
				case 12: NPCFight = std::stof(temp); break;
				case 13: NPCHeart = std::stof(temp); break;
			};
			counter++;
		}
	}
	IOFile.close();
}