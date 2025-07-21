#include "..//../header/RelicShower.h"

RelicShower::RelicShower()
{
	RelicImages = new sf::Image[7];
	RelicTextures = new sf::Texture[7];

	RelicImages[0].loadFromFile("Game\\Texture\\Map\\Relics\\spear-relic.png");
	RelicImages[1].loadFromFile("Game\\Texture\\Map\\Relics\\sword-relic.png");
	RelicImages[2].loadFromFile("Game\\Texture\\Map\\Relics\\trowel-relic.png");
	RelicImages[3].loadFromFile("Game\\Texture\\Map\\Relics\\cup-relic.png");
	RelicImages[4].loadFromFile("Game\\Texture\\Map\\Relics\\compass-relic.png");
	RelicImages[5].loadFromFile("Game\\Texture\\Map\\Relics\\ring-relic.png");
	RelicImages[6].loadFromFile("Game\\Texture\\Map\\Relics\\crown-relic.png");

	for (int i = 0; i < 7; ++i) {
		RelicTextures[i].loadFromImage(RelicImages[i]);
	}

	CurrectSprite.setScale(sf::Vector2f(0.3f, 0.3f));

	HiderShape.setFillColor(sf::Color(0, 0, 0, 128));
	HiderShape.setSize(sf::Vector2f(416, 320));
}

RelicShower::~RelicShower()
{
	if (RelicImages != nullptr) {
		delete[] RelicImages;
		RelicImages = nullptr;
	}
	if (RelicTextures != nullptr) {
		delete[] RelicTextures;
		RelicTextures = nullptr;
	}
}

void RelicShower::RelicDisplaier(sf::RenderWindow& MainWin, int Section, sf::Vector2f CameraCenterPos)
{
	HiderShape.setPosition(sf::Vector2f(CameraCenterPos.x - 208.f, CameraCenterPos.y - 160.f));
	CurrectSprite.setPosition(sf::Vector2f(CameraCenterPos.x - 75.f, CameraCenterPos.y - 75.f));
	CurrectSprite.setTexture(RelicTextures[Section]);
	MainWin.draw(HiderShape);
	MainWin.draw(CurrectSprite);
}

void RelicShower::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		IOFile << (int)RelicShow << std::endl;
		IOFile << RelicShowerTimer.asMilliseconds() << std::endl;
	}
	IOFile.close();
}

void RelicShower::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		while (getline(IOFile, temp)) {
			switch (counter) {
				case 0: RelicShow = std::stof(temp); break;
				case 1: RelicShowerTimer = sf::milliseconds(std::stof(temp)); break;
			};
			counter++;
		}
	}
	IOFile.close();
}