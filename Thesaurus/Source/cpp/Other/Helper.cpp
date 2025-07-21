#include "../../header/Helper.h"

Helper::Helper()
{
	DoorStatusImages = new sf::Image[7];
	RelicsImages = new sf::Image[8];
	HelpImages = new sf::Image[6];

	DoorStatusTextures = new sf::Texture[7];
	RelicsTextures = new sf::Texture[8];
	HelpTextures = new sf::Texture[6];

	DoorStatusSprites = new sf::Sprite[7];
	RelicsSprites = new sf::Sprite[7];
	HelpSprites = new sf::Sprite[6];
	ArrowsSprites = new sf::Sprite[7];
	KeysSprites = new sf::Sprite[3];

	DoorStatusImages[0].loadFromFile("Game\\Texture\\Map\\MapHelper\\keys-door-0.png");
	DoorStatusImages[1].loadFromFile("Game\\Texture\\Map\\MapHelper\\keys-door-1.png");
	DoorStatusImages[2].loadFromFile("Game\\Texture\\Map\\MapHelper\\keys-door-2.png");
	DoorStatusImages[3].loadFromFile("Game\\Texture\\Map\\MapHelper\\keys-door-3.png");

	RelicsImages[0].loadFromFile("Game\\Texture\\Map\\MapHelper\\spear.png");
	RelicsImages[1].loadFromFile("Game\\Texture\\Map\\MapHelper\\sword.png");
	RelicsImages[2].loadFromFile("Game\\Texture\\Map\\MapHelper\\trowel.png");
	RelicsImages[3].loadFromFile("Game\\Texture\\Map\\MapHelper\\cup.png");
	RelicsImages[4].loadFromFile("Game\\Texture\\Map\\MapHelper\\compass.png");
	RelicsImages[5].loadFromFile("Game\\Texture\\Map\\MapHelper\\ring.png");
	RelicsImages[6].loadFromFile("Game\\Texture\\Map\\MapHelper\\crown.png");
	RelicsImages[7].loadFromFile("Game\\Texture\\Map\\MapHelper\\relic-done.png");
	RelicsTextures[7].loadFromImage(RelicsImages[7]);

	HelpImages[0].loadFromFile("Game\\Texture\\Map\\MapHelper\\Q.png");
	HelpImages[1].loadFromFile("Game\\Texture\\Map\\MapHelper\\E.png");
	HelpImages[2].loadFromFile("Game\\Texture\\Map\\MapHelper\\F.png");
	HelpImages[3].loadFromFile("Game\\Texture\\Map\\MapHelper\\C.png");
	HelpImages[4].loadFromFile("Game\\Texture\\Map\\MapHelper\\X.png");
	HelpImages[5].loadFromFile("Game\\Texture\\Map\\MapHelper\\Left.png");

	ArrowImage.loadFromFile("Game\\Texture\\Map\\MapHelper\\arrow.png");
	ArrowTexture.loadFromImage(ArrowImage);

	KeyImage.loadFromFile("Game\\Texture\\Map\\MapHelper\\key.png");
	KeyTexture.loadFromImage(KeyImage);

	for (int i = 0; i < 3; ++i) {
		KeysSprites[i].setTexture(KeyTexture);
	}
	for (int i = 0; i < 4; ++i) {
		DoorStatusTextures[i].loadFromImage(DoorStatusImages[i]);
	}
	for (int i = 0; i < 7; ++i) {
		DoorStatusSprites[i].setTexture(DoorStatusTextures[0]);
		
		ArrowsSprites[i].setTexture(ArrowTexture);
		ArrowsSprites[i].setScale(sf::Vector2f(32.f / 489, 33.f / 510));
		
		RelicsTextures[i].loadFromImage(RelicsImages[i]);
		RelicsSprites[i].setTexture(RelicsTextures[i]);
		RelicsSprites[i].setScale(sf::Vector2f(0.5f, 0.5f));
	}

	HelpSpriteSize = sf::Vector2f(15.f, 15.f);
	for (int i = 0; i < 6; ++i) {
		HelpTextures[i].loadFromImage(HelpImages[i]);
		HelpSprites[i].setTexture(HelpTextures[i]);
		HelpSprites[i].setScale(sf::Vector2f(HelpSpriteSize.x / 500, HelpSpriteSize.y / 500));
	}

	DoorStatusSprites[0].setPosition(sf::Vector2f(247, 934));
	DoorStatusSprites[1].setPosition(sf::Vector2f(151, 518));
	DoorStatusSprites[2].setPosition(sf::Vector2f(311, 102));
	DoorStatusSprites[3].setPosition(sf::Vector2f(983, 102));
	DoorStatusSprites[4].setPosition(sf::Vector2f(951, 518));
	DoorStatusSprites[5].setPosition(sf::Vector2f(1079, 934));
	DoorStatusSprites[6].setPosition(sf::Vector2f(1399, 652));

	RelicsSprites[0].setPosition(sf::Vector2f(384, 787));
	RelicsSprites[1].setPosition(sf::Vector2f(33, 339));
	RelicsSprites[2].setPosition(sf::Vector2f(624, 191));
	RelicsSprites[3].setPosition(sf::Vector2f(1312, 339));
	RelicsSprites[4].setPosition(sf::Vector2f(960, 787));
	RelicsSprites[5].setPosition(sf::Vector2f(1363, 1024));
	RelicsSprites[6].setPosition(sf::Vector2f(1408, 339));

	ArrowsSprites[0].setPosition(sf::Vector2f(416, 896));
	ArrowsSprites[1].setPosition(sf::Vector2f(65, 448));
	ArrowsSprites[2].setPosition(sf::Vector2f(608, 224));
	ArrowsSprites[3].setPosition(sf::Vector2f(1312, 320));
	ArrowsSprites[4].setPosition(sf::Vector2f(960, 768));
	ArrowsSprites[5].setPosition(sf::Vector2f(1344, 1057));
	ArrowsSprites[6].setPosition(sf::Vector2f(1440, 448));

	ArrowsSprites[0].setRotation(90.f);
	ArrowsSprites[1].setRotation(90.f);
	ArrowsSprites[2].setRotation(180.f);
	ArrowsSprites[3].setRotation(270.f);
	ArrowsSprites[4].setRotation(270.f);
	ArrowsSprites[5].setRotation(180.f);
	ArrowsSprites[6].setRotation(90.f);

	
}

Helper::~Helper()
{
	if (DoorStatusImages != nullptr) {
		delete[] DoorStatusImages;
		DoorStatusImages = nullptr;
	}
	if (RelicsImages != nullptr) {
		delete[] RelicsImages;
		RelicsImages = nullptr;
	}
	if (HelpImages != nullptr) {
		delete[] HelpImages;
		HelpImages = nullptr;
	}

	if (DoorStatusTextures != nullptr) {
		delete[] DoorStatusTextures;
		DoorStatusTextures = nullptr;
	}
	if (RelicsTextures != nullptr) {
		delete[] RelicsTextures;
		RelicsTextures = nullptr;
	}
	if (HelpTextures != nullptr) {
		delete[] HelpTextures;
		HelpTextures = nullptr;
	}

	if (DoorStatusSprites != nullptr) {
		delete[] DoorStatusSprites;
		DoorStatusSprites = nullptr;
	}
	if (RelicsSprites != nullptr) {
		delete[] RelicsSprites;
		RelicsSprites = nullptr;
	}
	if (HelpSprites != nullptr) {
		delete[] HelpSprites;
		HelpSprites = nullptr;
	}
	if (ArrowsSprites != nullptr) {
		delete[] ArrowsSprites;
		ArrowsSprites = nullptr;
	}
	if (KeysSprites != nullptr) {
		delete[] KeysSprites;
		KeysSprites = nullptr;
	}
}

void Helper::HelperStaticDisplaier(sf::RenderWindow& MainWin, int section, int keys, sf::Vector2f CameraSize, sf::Vector2f CameraCenter)
{
	for (int i = 0; i < 7; ++i) {
		if (i < section) {
			RelicsSprites[i].setTexture(RelicsTextures[7]);
			DoorStatusSprites[i].setTexture(DoorStatusTextures[3]);
		}
		else if (i == section) {
			DoorStatusSprites[i].setTexture(DoorStatusTextures[keys]);
			RelicsSprites[i].setTexture(RelicsTextures[i]);
		}
		else {
			DoorStatusSprites[i].setTexture(DoorStatusTextures[0]);
			RelicsSprites[i].setTexture(RelicsTextures[i]);
		}
		MainWin.draw(RelicsSprites[i]);
		MainWin.draw(DoorStatusSprites[i]);
	}
	for (int i = 0; i < keys; ++i) {
		KeysSprites[i].setPosition(sf::Vector2f(CameraCenter.x + (CameraSize.x / 2) - (343 * 0.08f) * (CameraSize.x / 416.f) * (i + 1), CameraCenter.y - (CameraSize.y / 2)));
		KeysSprites[i].setScale((CameraSize.x / 416.f) * 0.08f, (CameraSize.y / 320.f) * 0.08f);
		MainWin.draw(KeysSprites[i]);
	}
}

void Helper::HelperArrowsDisplaier(sf::RenderWindow& MainWin)
{
	for (int i = 0; i < 7; ++i) {
		MainWin.draw(ArrowsSprites[i]);
	}
}

void Helper::HelperTempDisplaier(sf::RenderWindow& MainWin, int mode, sf::FloatRect itemPos)
{
	HelpSprites[mode].setPosition(sf::Vector2f(itemPos.left - HelpSpriteSize.x - ((mode == 5) ? 10 : 0), itemPos.top - HelpSpriteSize.y));
	MainWin.draw(HelpSprites[mode]);
}

void Helper::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		IOFile << tempMode << std::endl;
		IOFile << tempPosition.left << "\n" << tempPosition.top << "\n" << tempPosition.width << "\n" << tempPosition.height << std::endl;
		IOFile << (int)FPSChange << std::endl;
	}
	IOFile.close();
}

void Helper::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		while (getline(IOFile, temp)) {
			switch (counter) {
				case 0: tempMode = std::stof(temp); break;
				case 1: tempPosition.left = std::stof(temp); break;
				case 2: tempPosition.top = std::stof(temp); break;
				case 3: tempPosition.width = std::stof(temp); break;
				case 4: tempPosition.height = std::stof(temp); break;
				case 5: FPSChange = std::stof(temp); break;
			};
			counter++;
		}
	}
	IOFile.close();
}