#include "../../header/Keys.h"

Keys::Keys(sf::FloatRect* AreaArr, int ArrSize)
{
	srand(time(NULL));
	KeyImage.loadFromFile("Game\\Texture\\Map\\key.png");
	KeyTexture.loadFromImage(KeyImage);
	KeySprite.setTexture(KeyTexture);
	KeySpriteSize = sf::Vector2f(32.f, 32.f);
	KeySprite.setScale(KeySpriteSize.x / 500.f, KeySpriteSize.y / 500.f);

	KeysLocations = new sf::FloatRect[3];
	while (KeysLocationsSize < 3) {
		int tempI = (rand() % ArrSize);
		bool tempB = true;
		for (int i = 0; i < KeysLocationsSize; ++i) {
			if (KeysLocations[i] == AreaArr[tempI]) {
				tempB = false;
			}
		}
		if (tempB) {
			KeysLocations[KeysLocationsSize] = AreaArr[tempI];
			KeysLocationsSize++;
		}
	}
}

Keys::~Keys()
{
	if (KeysLocations != nullptr) {
		delete[] KeysLocations;
		KeysLocations = nullptr;
	}
}

void Keys::KeyDelete(int index)
{
	if (KeysLocationsSize - 1 != 0) {
		sf::FloatRect* tempArr = new sf::FloatRect[KeysLocationsSize - 1];
		for (int i = 0, j = 0; i < KeysLocationsSize; ++i) {
			if (i != index) {
				tempArr[j] = KeysLocations[i];
				j++;
			}
		}
		delete[] KeysLocations;
		KeysLocations = tempArr;
	}
	if (KeysLocationsSize > 0) {
		KeysLocationsSize--;
	}
}

int Keys::KeysController(sf::FloatRect HeroLocation, bool deleteB)
{
	for (int i = 0; i < KeysLocationsSize; ++i) {
		if (KeysLocations[i].intersects(HeroLocation)) {
			if (deleteB) {
				KeyDelete(i);
			}
			return i;
		}
	}
	return -1;
}

void Keys::KeysDisplaier(sf::RenderWindow& MainWin, sf::FloatRect HeroLocation)
{
	for (int i = 0; i < KeysLocationsSize; ++i) {
		if (KeysLocations[i].intersects(HeroLocation)) {
			KeySprite.setPosition(KeysLocations[i].left, KeysLocations[i].top);
			MainWin.draw(KeySprite);
		}
	}
}

void Keys::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		if (KeysLocationsSize != 0) {
			IOFile << KeysLocationsSize << std::endl;
			for (int j = 0; j < KeysLocationsSize; ++j) {
				IOFile << KeysLocations[j].left << "\n" << KeysLocations[j].top << std::endl;
			}
		}
		else {
			IOFile << '0' << std::endl;
		}
	}
	IOFile.close();
}

void Keys::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		while (getline(IOFile, temp)) {
			switch (counter) {
				case 0: KeysLocationsSize = stof(temp); break;
			};
			if (KeysLocationsSize) {
				if (counter >= 1 && counter < (KeysLocationsSize * 2) + 1) {
					if (counter % 2) {
						KeysLocations[(counter - 1) / 2].left = std::stof(temp);
					}
					else {
						KeysLocations[(counter - 1) / 2].top = std::stof(temp);
					}
				}
			}
			counter++;
		}
	}
	IOFile.close();
}