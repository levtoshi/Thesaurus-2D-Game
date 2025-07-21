#include "../../header/Play.h"

sf::FloatRect* Play::FitArr(sf::FloatRect* arr, int size) {
	sf::FloatRect* newArr = new sf::FloatRect[size];
	for (int i = 0; i < size; ++i)
		newArr[i] = arr[i];
	delete[] arr;
	return newArr;
}

void Play::DeleteArrElement(auto*& arr, int& size, int index) {
	if (size > 1) {
		sf::FloatRect* tempArr = new sf::FloatRect[size - 1];
		for (int i = 0, j = 0; i < size; ++i) {
			if (i != index) {
				tempArr[j] = arr[i];
				j++;
			}
		}
		delete[] arr;
		arr = tempArr;
	}
	else {
		delete[] arr;
		arr = nullptr;
	}
	if (size > 0) {
		size--;
	}
}

void Play::FillKeysAreaArray(sf::FloatRect areaRect, sf::FloatRect* arr, int& index)
{
	int tempRow, tempCol;
	for (int i = 0; i < (areaRect.height / 32); ++i) {
		for (int j = 0; j < (areaRect.width / 32); ++j) {
			tempRow = ((areaRect.top + (32 * i)) / 32);
			tempCol = ((areaRect.left + (32 * j)) / 32);
			if (PlayMaps[1]->MapDownMatrix[tempRow][tempCol] != '5' &&
				PlayMaps[1]->MapDownMatrix[tempRow][tempCol] != '6' &&
				PlayMaps[1]->MapUpMatrix[tempRow][tempCol] != 'c' &&
				PlayMaps[1]->MapUpMatrix[tempRow][tempCol] != 'd' &&
				PlayMaps[1]->MapUpMatrix[tempRow][tempCol] != 'e' &&
				PlayMaps[1]->MapUpMatrix[tempRow][tempCol] != 'f') {
				arr[index] = sf::FloatRect(areaRect.left + (32 * j), areaRect.top + (32 * i), 32, 32);
				index++;
			}

		}
	}
}

Play::Play()
{
	PlayHero = new Hero;
	// Maps
	PlayMaps[0] = new Map("Game\\Texture\\Map\\start.txt");
	PlayMaps[1] = new Map("Game\\Texture\\Map\\map.txt");
	PlayMaps[2] = new Map("Game\\Texture\\Map\\chess.txt");

	// Collision
	StaticCollision = new PlayPos[4];
	for (int i = 0; i < 3; ++i) {
		StaticCollision[i].ObjectsArray = new sf::FloatRect[2500];
		StaticCollision[i].ArraySize = PlayMaps[i]->CollisionObjectsDetector(StaticCollision[i].ObjectsArray);
		StaticCollision[i].ObjectsArray = FitArr(StaticCollision[i].ObjectsArray, StaticCollision[i].ArraySize);
	}
	StaticCollision[3] = StaticCollision[0];

	// Temp Collision
	TempCollision = new PlayPos[2];
	TempCollision[0].ArraySize = 7;
	TempCollision[1].ArraySize = 7;

	TempCollision[0].ObjectsArray = new sf::FloatRect[TempCollision[0].ArraySize];
	TempCollision[1].ObjectsArray = new sf::FloatRect[TempCollision[1].ArraySize];

	TempCollision[0].ObjectsArray[0] = sf::FloatRect(268, 958, 12, 7);
	TempCollision[0].ObjectsArray[1] = sf::FloatRect(172, 537, 12, 7);
	TempCollision[0].ObjectsArray[2] = sf::FloatRect(332, 121, 12, 7);
	TempCollision[0].ObjectsArray[3] = sf::FloatRect(1004, 121, 12, 7);
	TempCollision[0].ObjectsArray[4] = sf::FloatRect(972, 537, 12, 7);
	TempCollision[0].ObjectsArray[5] = sf::FloatRect(1100, 958, 12, 7);
	TempCollision[0].ObjectsArray[6] = sf::FloatRect(1420, 665, 12, 7);

	TempCollision[1].ObjectsArray[0] = sf::FloatRect(398, 825, 12, 7);
	TempCollision[1].ObjectsArray[1] = sf::FloatRect(44, 377, 12, 7);
	TempCollision[1].ObjectsArray[2] = sf::FloatRect(640, 204, 7, 12);
	TempCollision[1].ObjectsArray[3] = sf::FloatRect(1324, 377, 12, 7);
	TempCollision[1].ObjectsArray[4] = sf::FloatRect(972, 825, 12, 7);
	TempCollision[1].ObjectsArray[5] = sf::FloatRect(1376, 1036, 7, 12);
	TempCollision[1].ObjectsArray[6] = sf::FloatRect(1420, 377, 12, 7);

	// Camera
	PlayCamera = new Camera;
	PlayCamera->ViewSizeConst = sf::Vector2f(205.71f, 160.f);
	PlayCamera->ViewSize = PlayCamera->ViewSizeConst;
	PlayCamera->CameraView.setSize(PlayCamera->ViewSize);

	PlayCamera->MapSize = sf::Vector2f(PlayMaps[0]->MapSize);
	PlayCamera->HeroSize = sf::Vector2f(PlayHero->HeroSize);
	PlayHero->HeroSprite.setPosition(32, 256);

	// Esc icon
	EscImage.loadFromFile("Game\\Texture\\Map\\esc.png");
	EscTexture.loadFromImage(EscImage);
	EscSprite.setTexture(EscTexture);

	// Sounds
	PlaySoundBuffer = new sf::SoundBuffer[9];
	PlaySoundBuffer[0].loadFromFile("Game\\Audio\\walking.wav");
	PlaySoundBuffer[1].loadFromFile("Game\\Audio\\collision.wav");
	PlaySoundBuffer[2].loadFromFile("Game\\Audio\\key.wav");
	PlaySoundBuffer[3].loadFromFile("Game\\Audio\\relic.wav");
	PlaySoundBuffer[4].loadFromFile("Game\\Audio\\newLevel.wav");
	PlaySoundBuffer[5].loadFromFile("Game\\Audio\\door-open.mp3");
	PlaySoundBuffer[6].loadFromFile("Game\\Audio\\victory.mp3");
	PlaySoundBuffer[7].loadFromFile("Game\\Audio\\sword-sound.mp3");
	PlaySoundBuffer[8].loadFromFile("Game\\Audio\\fail.wav");
	PlaySounds = new sf::Sound[9];
	for (int i = 0; i < 9; ++i) {
		PlaySounds[i].setBuffer(PlaySoundBuffer[i]);
	}

	// Keys

	// 1
	sf::FloatRect* tempArr = new sf::FloatRect[700];
	int tempIndex = 0;
	sf::FloatRect tempRect = sf::FloatRect(96, 1120, 544, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(448, 864, 192, 96);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	MapKeysArr[0] = new Keys(tempArr, tempIndex);
	delete[] tempArr;
	tempArr = new sf::FloatRect[700];
	tempIndex = 0;

	// 2
	tempRect = sf::FloatRect(0, 704, 352, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(448, 416, 192, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(448, 704, 192, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	MapKeysArr[1] = new Keys(tempArr, tempIndex);
	delete[] tempArr;
	tempArr = new sf::FloatRect[700];
	tempIndex = 0;

	// 3
	tempRect = sf::FloatRect(96, 288, 544, 96);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(448, 32, 192, 96);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	MapKeysArr[2] = new Keys(tempArr, tempIndex);
	delete[] tempArr;
	tempArr = new sf::FloatRect[700];
	tempIndex = 0;

	// 4
	tempRect = sf::FloatRect(640, 32, 288, 96);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(640, 288, 640, 96);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	MapKeysArr[3] = new Keys(tempArr, tempIndex);
	delete[] tempArr;
	tempArr = new sf::FloatRect[700];
	tempIndex = 0;

	// 5
	tempRect = sf::FloatRect(640, 416, 288, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(640, 704, 288, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(1024, 704, 352, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	MapKeysArr[4] = new Keys(tempArr, tempIndex);
	delete[] tempArr;
	tempArr = new sf::FloatRect[700];
	tempIndex = 0;

	// 6
	tempRect = sf::FloatRect(640, 864, 288, 96);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(640, 1120, 736, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	MapKeysArr[5] = new Keys(tempArr, tempIndex);
	delete[] tempArr;
	tempArr = new sf::FloatRect[700];
	tempIndex = 0;

	// 7
	tempRect = sf::FloatRect(1472, 416, 448, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(1376, 864, 448, 96);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	tempRect = sf::FloatRect(1376, 1120, 544, 128);
	FillKeysAreaArray(tempRect, tempArr, tempIndex);
	MapKeysArr[6] = new Keys(tempArr, tempIndex);
	delete[] tempArr;
	tempArr = nullptr;

	// Cases
	CasesPositions = new sf::FloatRect[7];
	CasesPositions[0] = sf::FloatRect(32, 864, 32, 32);
	CasesPositions[1] = sf::FloatRect(416, 448, 32, 32);
	CasesPositions[2] = sf::FloatRect(32, 64, 32, 32);
	CasesPositions[3] = sf::FloatRect(1344, 64, 32, 32);
	CasesPositions[4] = sf::FloatRect(1216, 416, 32, 32);
	CasesPositions[5] = sf::FloatRect(1344, 896, 32, 32);
	CasesPositions[6] = sf::FloatRect(1760, 736, 32, 32);

	for (int i = 0; i < 7; ++i) {
		CasesStates[i] = true;
	}

	ShowRelicObject = new RelicShower;

	// Password
	tempArr = new sf::FloatRect[7];
	tempArr[0] = sf::FloatRect(32, 832, 32, 32);
	tempArr[1] = sf::FloatRect(416, 384, 32, 32);
	tempArr[2] = sf::FloatRect(32, 0, 32, 32);
	tempArr[3] = sf::FloatRect(1344, 0, 32, 32);
	tempArr[4] = sf::FloatRect(1216, 384, 32, 32);
	tempArr[5] = sf::FloatRect(1344, 832, 32, 32);
	tempArr[6] = sf::FloatRect(1760, 672, 32, 32);
	PlayPassword = new Password(tempArr);
	delete[] tempArr;
	tempArr = nullptr;

	// Map Hider
	MapHiderObject = new MapHider;

	// Helper
	HelperObject = new Helper;

	//NPC
	NPCStaticPositions = new PlayPos;
	
	sf::Vector2f* yCoordTemp = new sf::Vector2f[7] {sf::Vector2f(96, 864), sf::Vector2f(288, 416), sf::Vector2f(96, 32),
		sf::Vector2f(1216, 32), sf::Vector2f(1088, 416), sf::Vector2f(1216, 864), sf::Vector2f(1632, 704) };

	NPCStaticPositions->ArraySize = 7;
	NPCStaticPositions->ObjectsArray = new sf::FloatRect[NPCStaticPositions->ArraySize];
	for (int i = 0; i < NPCStaticPositions->ArraySize; ++i) {
		NPCStaticPositions->ObjectsArray[i] = sf::FloatRect(yCoordTemp[i].x, yCoordTemp[i].y, 32, 32);
	}

	delete[] yCoordTemp;
	yCoordTemp = nullptr;

	HiderShape.setFillColor(sf::Color(0, 0, 0, 128));
	HiderShape.setSize(sf::Vector2f(416, 320));
	TextFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
	DeadText.setFillColor(sf::Color::White);
	DeadText.setCharacterSize(36);
	DeadText.setFont(TextFont);
	DeadText.setString(L"Програш!");
}

Play::~Play()
{
	if (PlayHero != nullptr) {
		delete PlayHero;
		PlayHero = nullptr;
	}
	if (PlayCamera != nullptr) {
		delete PlayCamera;
		PlayCamera = nullptr;
	}
	if (PlayMaps != nullptr) {
		delete PlayMaps[0];
		delete PlayMaps[1];
		delete PlayMaps[2];
	}
	if (StaticCollision != nullptr) {
		delete[] StaticCollision;
		StaticCollision = nullptr;
	}
	if (PlaySoundBuffer != nullptr) {
		delete[] PlaySoundBuffer;
		PlaySoundBuffer = nullptr;
	}
	if (PlaySounds != nullptr) {
		delete[] PlaySounds;
		PlaySounds = nullptr;
	}
	if (MapKeysArr != nullptr) {
		delete MapKeysArr[0];
		delete MapKeysArr[1];
		delete MapKeysArr[2];
		delete MapKeysArr[3];
		delete MapKeysArr[4];
		delete MapKeysArr[5];
		delete MapKeysArr[6];
	}
	if (CasesPositions != nullptr) {
		delete[] CasesPositions;
		CasesPositions = nullptr;
	}
	if (TempCollision != nullptr) {
		for (int i = 0; i < 2; ++i) {
			if (TempCollision[i].ObjectsArray != nullptr) {
				delete[] TempCollision[i].ObjectsArray;
				TempCollision[i].ObjectsArray = nullptr;
			}
		}
		delete[] TempCollision;
		TempCollision = nullptr;
	}
	if (PlayPassword != nullptr) {
		delete PlayPassword;
		PlayPassword = nullptr;
	}
	if (MapHiderObject != nullptr) {
		delete MapHiderObject;
		MapHiderObject = nullptr;
	}
	if (ShowRelicObject != nullptr) {
		delete ShowRelicObject;
		ShowRelicObject = nullptr;
	}

	if (HelperObject != nullptr) {
		delete HelperObject;
		HelperObject = nullptr;
	}
	if (PlayNPC != nullptr) {
		delete PlayNPC;
		PlayNPC = nullptr;
	}
	if (NPCStaticPositions != nullptr) {
		delete NPCStaticPositions;
		NPCStaticPositions = nullptr;
	}
}

void Play::PlayDisplaier(sf::RenderWindow& MainWin)
{
	if (!DYNAMIC) {
		DYNAMIC = true;
	}
	MainWin.clear(sf::Color::Black);
	MainWin.setView(PlayCamera->CameraView);
	for (int i = 0; i < 3; ++i) {
		if (CurrentMap == i) {
			PlayMaps[i]->MapDisplaierDown(MainWin);
			if (CurrentMap == GAME_MAP) {
				for (int j = 0; j < 7; ++j) {
					MapKeysArr[j]->KeysDisplaier(MainWin, PlayHero->HeroSprite.getGlobalBounds());
				}
				PlayPassword->PasswordWallDisplaier(MainWin);
				HelperObject->HelperArrowsDisplaier(MainWin);
				
				if (PlayFight) {
					PlayNPC->NPCDisplaier(MainWin);
				}
				PlayHero->HeroDisplaier(MainWin);

				PlayMaps[i]->MapDisplaierUp(MainWin);
				MapHiderObject->HiderDislaier(MainWin, CurrentSection);
				HelperObject->HelperStaticDisplaier(MainWin, CurrentSection, PlayHero->HeroKeysAmount, PlayCamera->ViewSize, PlayCamera->ViewCenter);
				if (HelperObject->FPSChange) {
					HelperObject->HelperTempDisplaier(MainWin, HelperObject->tempMode, HelperObject->tempPosition);
					HelperObject->FPSChange = false;
				}
				if (PasswordWinOpened) {
					PlayPassword->PasswordWindowDisplaier(MainWin);
				}
				if (ShowRelicObject->RelicShow) {
					ShowRelicObject->RelicDisplaier(MainWin, CurrentSection, PlayCamera->ViewCenter);
				}
				if (HeroDeadBoolean) {
					HeroDeadShower(MainWin);
				}
			}
			else {
				PlayHero->HeroDisplaier(MainWin);
				PlayMaps[i]->MapDisplaierUp(MainWin);
			}
		}
	}
	MainWin.draw(EscSprite);
	
}

void Play::HeroDeadShower(sf::RenderWindow& MainWin)
{
	HiderShape.setPosition(sf::Vector2f(PlayCamera->ViewCenter.x - 208.f, PlayCamera->ViewCenter.y - 160.f));
	DeadText.setPosition(sf::Vector2f(PlayCamera->ViewCenter.x - 80, PlayCamera->ViewCenter.y - 20));
	MainWin.draw(HiderShape);
	MainWin.draw(DeadText);
}

bool Play::PlayController(sf::RenderWindow& MainWin)
{
	// Hero Moving
	if (!PasswordWinOpened && !ShowRelicObject->RelicShow && !HeroDeadBoolean) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			PlayHero->HeroMove(1, StaticCollision[3].ObjectsArray, StaticCollision[3].ArraySize,
				TempCollision[0].ObjectsArray, TempCollision[0].ArraySize,
				TempCollision[1].ObjectsArray, TempCollision[1].ArraySize, PlaySounds);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			PlayHero->HeroMove(2, StaticCollision[3].ObjectsArray, StaticCollision[3].ArraySize,
				TempCollision[0].ObjectsArray, TempCollision[0].ArraySize,
				TempCollision[1].ObjectsArray, TempCollision[1].ArraySize, PlaySounds);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			PlayHero->HeroMove(3, StaticCollision[3].ObjectsArray, StaticCollision[3].ArraySize,
				TempCollision[0].ObjectsArray, TempCollision[0].ArraySize,
				TempCollision[1].ObjectsArray, TempCollision[1].ArraySize, PlaySounds);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			PlayHero->HeroMove(4, StaticCollision[3].ObjectsArray, StaticCollision[3].ArraySize,
				TempCollision[0].ObjectsArray, TempCollision[0].ArraySize,
				TempCollision[1].ObjectsArray, TempCollision[1].ArraySize, PlaySounds);
		}
		else {
			PlayHero->HeroStand();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		PlayCamera->CameraReset();
	}
	if (CurrentMap == GAME_MAP) {
		sf::FloatRect tempF;
		if (CurrentSection != 7) {
			int temp = MapKeysArr[CurrentSection]->KeysController(PlayHero->HeroSprite.getGlobalBounds(), false);
			if (temp != -1) {
				HelperObject->FPSChange = true;
				HelperObject->tempMode = 0;
				HelperObject->tempPosition = MapKeysArr[CurrentSection]->KeysLocations[temp];
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
					if (MapKeysArr[CurrentSection]->KeysController(PlayHero->HeroSprite.getGlobalBounds(), true) != -1) {
						if (PlaySounds[2].getStatus() != sf::Sound::Status::Playing) {
							PlaySounds[2].play();
						}
						PlayHero->HeroKeysAmount++;
					}
				}
			}
		}
		if (TempCollision[0].ObjectsArray != nullptr && !PlayFight) {
			tempF = TempCollision[0].ObjectsArray[0];
			tempF.top -= 32;
			tempF.height += 64;
			tempF.left -= 32;
			tempF.width += 64;
			if (PlayHero->HeroKeysAmount == 3 && tempF.intersects(PlayHero->HeroSprite.getGlobalBounds())) {
				HelperObject->FPSChange = true;
				HelperObject->tempMode = 1;
				HelperObject->tempPosition = TempCollision[0].ObjectsArray[0];
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					PlayFight = true;
					PlayHero->HeroSprite.setPosition(sf::Vector2f(PlayHero->HeroSprite.getGlobalBounds().left, PlayHero->HeroSprite.getGlobalBounds().top + ((CurrentSection == 6) ? 75 : - 75)));
					PlayMaps[1]->ChangeDoorToOpened(TempCollision[0].ObjectsArray[0]);
					if (PlaySounds[5].getStatus() != sf::Sound::Status::Playing) {
						PlaySounds[5].play();
					}
				}
			}
		}

		if (CasesPositions[CurrentSection].intersects(PlayHero->HeroSprite.getGlobalBounds()) && CasesStates[CurrentSection] && !PlayFight) {
			HelperObject->FPSChange = true;
			HelperObject->tempMode = 2;
			HelperObject->tempPosition = CasesPositions[CurrentSection];
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				PlayMaps[1]->ChangeCaseToOpened(CasesPositions[CurrentSection]);
				if (PlaySounds[3].getStatus() != sf::Sound::Status::Playing) {
					PlaySounds[3].play();
				}
				PlayHero->HeroRelic = true;
				BetweenFightAndRelic = false;
				CasesStates[CurrentSection] = false;
				ShowRelicObject->RelicShow = true;
				PlayCamera->CameraReset();
			}
		}

		if (TempCollision[1].ArraySize > 1) {
			tempF = TempCollision[1].ObjectsArray[0];
			tempF.top -= 32;
			tempF.height += 64;
			tempF.left -= 32;
			tempF.width += 64;
			if (PlayHero->HeroRelic && tempF.intersects(PlayHero->HeroSprite.getGlobalBounds())) {
				HelperObject->FPSChange = true;
				HelperObject->tempMode = 3;
				HelperObject->tempPosition = TempCollision[1].ObjectsArray[0];
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
					if (CurrentSection != 2 && CurrentSection != 5) {
						PlayMaps[1]->ChangeSectionToOpen(TempCollision[1].ObjectsArray[0]);
					}
					DeleteArrElement(TempCollision[1].ObjectsArray, TempCollision[1].ArraySize, 0);
					if (PlaySounds[4].getStatus() != sf::Sound::Status::Playing) {
						PlaySounds[4].play();
					}
					CurrentSection++;
					PlayHero->HeroKeysAmount = 0;
					PlayHero->HeroRelic = false;
					PlayHero->HeroHeart = 5;
				}
			}
		}
		if (TempCollision[1].ObjectsArray != nullptr) {
			tempF = TempCollision[1].ObjectsArray[0];
			tempF.top -= 32;
			tempF.height += 64;
			tempF.left -= 32;
			tempF.width += 64;
			if (CurrentSection == 6 && tempF.intersects(PlayHero->HeroSprite.getGlobalBounds()) && PlayHero->HeroRelic) {
				HelperObject->FPSChange = true;
				HelperObject->tempMode = 4;
				HelperObject->tempPosition = TempCollision[1].ObjectsArray[0];
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
					PlayCamera->CameraReset();
					PlayCamera->ViewCenter = sf::Vector2f(1424, 432);
					PlayCamera->CameraView.setCenter(PlayCamera->ViewCenter);
					PasswordWinOpened = true;
				}
			}
		}

		if (PlayFight && PlayNPC != nullptr) {
			if (PlayHero->HeroSprite.getGlobalBounds().intersects(PlayNPC->NPCSprite.getGlobalBounds()) && !PlayHero->HeroFight) {
				HelperObject->FPSChange = true;
				HelperObject->tempMode = 5;
				HelperObject->tempPosition = PlayNPC->NPCSprite.getGlobalBounds();
			}
		}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		//	PlayHero->HeroKeysAmount = 3;
		//}
	}
	if (!HeroDeadBoolean) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return true;
		}
	}
	else {
		if (DeadTime.asMilliseconds() > ShowDeadMessageTime) {
			return true;
		}
	}
	
	return false;
}

void Play::PlayUpdater(sf::Clock& MainClock, float MainVolume)
{
	if (PlayFight) {
		PlayFightFunc(MainClock);
		if (PlayFight) {
			PlayHero->NPCPosition = sf::FloatRect(PlayNPC->NPCCurrentPos.left + 15, PlayNPC->NPCCurrentPos.top + 2, PlayNPC->NPCCurrentPos.width - 15, PlayNPC->NPCCurrentPos.height - 30);
		}
		else {
			PlayHero->NPCPosition = sf::FloatRect(0,0,0,0);
		}
	}
	if (HeroDeadBoolean) {
		DeadTime += MainClock.restart();
	}
	else {
		if (ShowRelicObject->RelicShow) {
			if (ShowRelicObject->RelicShowerTimer.asMilliseconds() < ShowRelicObject->RelicShowTime) {
				PlayHero->HeroMoveTime = MainClock.getElapsedTime();
				ShowRelicObject->RelicShowerTimer += MainClock.restart();
			}
			else {
				ShowRelicObject->RelicShow = false;
				ShowRelicObject->RelicShowerTimer = sf::Time::Zero;
				PlayHero->HeroMoveTime = MainClock.restart();
			}
		}
		else {
			if (PlayFight) {

				PlayNPC->NPCMainTime = MainClock.getElapsedTime();
			}
			PlayHero->HeroMoveTime = MainClock.restart();
		}
	}

	if (sf::FloatRect(32, 0, 32, 33).intersects(PlayHero->HeroSprite.getGlobalBounds()) && CurrentMap == START) {
		CurrentMap = GAME_MAP;
		StaticCollision[3] = StaticCollision[1];

		PlayCamera->ViewSizeConst = sf::Vector2f(416.f, 320.f);
		PlayCamera->ViewSize = PlayCamera->ViewSizeConst;
		PlayCamera->CameraView.reset(sf::FloatRect(0.f, 960.f, PlayCamera->ViewSize.x, PlayCamera->ViewSize.y));
		PlayCamera->MapSize = sf::Vector2f(PlayMaps[1]->MapSize);
		PlayHero->HeroSprite.setPosition(32, 1184);
	}
	if (sf::FloatRect(1632, 0, 32, 32).intersects(PlayHero->HeroSprite.getGlobalBounds()) && CurrentMap == GAME_MAP) {
		CurrentMap = CHESS;
		StaticCollision[3] = StaticCollision[2];

		PlayCamera->ViewSizeConst = sf::Vector2f(205.71f, 160.f);
		PlayCamera->ViewSize = PlayCamera->ViewSizeConst;
		PlayCamera->CameraView.setSize(PlayCamera->ViewSize);
		PlayCamera->MapSize = sf::Vector2f(PlayMaps[2]->MapSize);

		PlayHero->HeroSprite.setPosition(176, 640);
	}
	if (!PasswordWinOpened && !HeroDeadBoolean) {
		PlayCamera->CameraUpdater(PlayHero->HeroSprite.getPosition());
	}
	EscSprite.setPosition(sf::Vector2f(PlayCamera->ViewCenter.x - (PlayCamera->ViewSize.x / 2), PlayCamera->ViewCenter.y - (PlayCamera->ViewSize.y / 2)));
	EscSprite.setScale((PlayCamera->ViewSize.x / PlayCamera->ViewSizeConst.x) / (8000.f / PlayCamera->ViewSizeConst.x), (PlayCamera->ViewSize.y / PlayCamera->ViewSizeConst.y) / (8000.f / PlayCamera->ViewSizeConst.x));
}

void Play::PlayFightFunc(sf::Clock& MainClock)
{
	if (PlayNPC == nullptr) {
		PlayNPC = new NPC;
		PlayNPC->NPCCurrentPos = NPCStaticPositions->ObjectsArray[CurrentSection];
		PlayNPC->NPCSprite.setPosition(PlayNPC->NPCCurrentPos.left, PlayNPC->NPCCurrentPos.top);
	}

	PlayNPC->NPCMainTime = MainClock.getElapsedTime();
	sf::FloatRect tempPos = sf::FloatRect(PlayHero->HeroSprite.getGlobalBounds().left + 15, PlayHero->HeroSprite.getGlobalBounds().top + 15,
		PlayHero->HeroSprite.getGlobalBounds().width - 15, PlayHero->HeroSprite.getGlobalBounds().height - 15);
	
	PlayNPC->NPCMove(PlayHero->HeroSprite.getGlobalBounds(), tempPos, StaticCollision[3].ObjectsArray, StaticCollision[3].ArraySize,
		TempCollision[0].ObjectsArray, TempCollision[0].ArraySize,
		TempCollision[1].ObjectsArray, TempCollision[1].ArraySize);
	PlayNPC->NPCHeart -= PlayHero->HeroFightFunc(PlayNPC->NPCCurrentPos);
	PlayHero->HeroHeart -= PlayNPC->NPCFightFunc();

	if (PlayHero->HeroFightFunc(PlayNPC->NPCCurrentPos) || PlayNPC->NPCFightFunc()) {
		if (PlaySounds[7].getStatus() != sf::Sound::Status::Playing) {
			PlaySounds[7].play();
		}
	}

	if (PlayHero->HeroHeart <= 0) {
		DeleteArrElement(TempCollision[0].ObjectsArray, TempCollision[0].ArraySize, 0);
		PlayFight = false;
		PlaySounds[8].play();
		HeroDeadBoolean = true;
		PlayCamera->CameraReset();
	}
	if (PlayFight) {
		if (PlayNPC->NPCHeart <= 0) {
			DeleteArrElement(TempCollision[0].ObjectsArray, TempCollision[0].ArraySize, 0);
			PlayFight = false;
			BetweenFightAndRelic = true;
			delete PlayNPC;
			PlayNPC = nullptr;
		}
	}
}


void Play::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		IOFile << CurrentMap << std::endl;
		if (TempCollision[0].ObjectsArray != nullptr) {
			IOFile << TempCollision[0].ArraySize << std::endl;
		}
		else {
			IOFile << 0 << std::endl;
		}
		if (TempCollision[1].ObjectsArray != nullptr) {
			IOFile << TempCollision[1].ArraySize << std::endl;
		}
		else {
			IOFile << 0 << std::endl;
		}
		IOFile << CurrentSection << std::endl;
		IOFile << PasswordWinOpened << std::endl;
		IOFile << PlayFight << std::endl;
		IOFile << BetweenFightAndRelic << std::endl;
		IOFile << PlayHero->HeroRelic << std::endl;
		for (int i = 0; i < 7; ++i) {
			IOFile << CasesStates[i] << std::endl;
		}
	}
	IOFile.close();
}

void Play::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	int temp1 = 0;
	int temp2 = 0;
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		while (getline(IOFile, temp)) {
			switch (counter) {
				case 0: CurrentMap = (MapEnum)std::stof(temp); break;
				case 1: temp1 = std::stof(temp); break;
				case 2: temp2 = std::stof(temp); break;
				case 3: CurrentSection = std::stof(temp); break;
				case 4: PasswordWinOpened = (int)std::stof(temp); break;
				case 5: PlayFight = (int)std::stof(temp); break;
				case 6: BetweenFightAndRelic = (int)std::stof(temp); break;
				case 7: PlayHero->HeroRelic = (int)std::stof(temp); break;
			};
			if (counter > 7 && counter < 15) {
				CasesStates[counter - 8] = (int)std::stof(temp);
			}
			counter++;
		}
	}
	if (TempCollision[0].ArraySize) {
		for (int i = 0; i < 7 - temp1; ++i) {
			DeleteArrElement(TempCollision[0].ObjectsArray, TempCollision[0].ArraySize, 0);
		}
	}
	else {
		TempCollision[0].ObjectsArray = nullptr;
		TempCollision[0].ArraySize = 0;
	}
	if (TempCollision[1].ArraySize) {
		for (int i = 0; i < 7 - temp2; ++i) {
			DeleteArrElement(TempCollision[1].ObjectsArray, TempCollision[1].ArraySize, 0);
		}
	}
	else {
		TempCollision[1].ObjectsArray = nullptr;
		TempCollision[1].ArraySize = 0;
	}
	IOFile.close();
}