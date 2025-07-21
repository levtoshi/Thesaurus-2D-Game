#include "../../header/Map.h"

Map::Map(std::string address)
{
	this->ReadFilePath = address;
	ReadFile.open(ReadFilePath);

	if (ReadFile.is_open()) {
		std::string tempStr;
		int tempCounter = 0;
		while (getline(ReadFile, tempStr)) {
			if (!tempCounter) {
				MapTeilsetPath = tempStr;
			}
			else if (tempCounter == 1) {
				MapColsDown = std::stoi(tempStr) + 1;
				MapRowsDown = std::atoi(tempStr.c_str() + tempStr.find(' '));

				MapDownMatrix = new unsigned char*[MapRowsDown];
				for (int i = 0; i < MapRowsDown; ++i) {
					MapDownMatrix[i] = new unsigned char[MapColsDown];
				}
			}
			else if (tempCounter == 2) {
				MapColsUp = std::stoi(tempStr) + 1;
				MapRowsUp = std::atoi(tempStr.c_str() + tempStr.find(' '));

				MapUpMatrix = new unsigned char* [MapRowsUp];
				for (int i = 0; i < MapRowsUp; ++i) {
					MapUpMatrix[i] = new unsigned char[MapColsUp];
				}
			}
			else if (tempCounter == 3) {
				RectSize.x = std::stoi(tempStr);
				RectSize.y = std::atoi(tempStr.c_str() + tempStr.find(' '));
			}
			else if (tempCounter <= MapRowsDown + 3) {
				for (int i = 0; i < tempStr.length(); ++i) {
					MapDownMatrix[tempCounter - 4][i] = tempStr[i];
				}
			}
			else if (tempCounter <= MapRowsDown + MapRowsUp + 3) {
				for (int i = 0; i < tempStr.length(); ++i) {
					MapUpMatrix[tempCounter - MapRowsDown - 4][i] = tempStr[i];
				}
			}
			else if (tempCounter == (MapRowsDown + MapRowsUp + 4)) {
				RectAmount = std::stoi(tempStr) + 1;
				TeilsetRects = new MapRectInfo[RectAmount];
			}
			else if (tempCounter <= MapRowsDown + MapRowsUp + 4 + RectAmount) {
				TeilsetRects[tempCounter - (MapRowsDown + MapRowsUp + 5)].RectChar = (char)tempStr[0];
				TeilsetRects[tempCounter - (MapRowsDown + MapRowsUp + 5)].RectPos.left = atoi(tempStr.c_str() + 1);
				const char* temp = strchr(tempStr.c_str() + 2, ' ');
				TeilsetRects[tempCounter - (MapRowsDown + MapRowsUp + 5)].RectPos.top = atoi(temp);
				temp = strchr(temp + 1, ' ');
				TeilsetRects[tempCounter - (MapRowsDown + MapRowsUp + 5)].RectPos.width = atoi(temp);
				temp = strchr(temp + 1, ' ');
				TeilsetRects[tempCounter - (MapRowsDown + MapRowsUp + 5)].RectPos.height = atoi(temp);
			}
			tempCounter++;
		}
	}
	ReadFile.close();

	MapSize = sf::Vector2f((MapColsDown - 1) * RectSize.x, MapRowsDown * RectSize.y);

	MapImage.loadFromFile(MapTeilsetPath);
	MapTexture.loadFromImage(MapImage);
	MapSprite.setTexture(MapTexture);

	OpenedCaseImage.loadFromFile("Game\\Texture\\Map\\opened-case.png");
	OpenedCaseTexture.loadFromImage(OpenedCaseImage);
	OpenedCaseSprite.setTexture(OpenedCaseTexture);

	ChessDesk = new Chess;
}

Map::~Map()
{
	if (TeilsetRects != nullptr) {
		delete[] TeilsetRects;
		TeilsetRects = nullptr;
	}
	if (MapDownMatrix != nullptr) {
		for (int i = 0; i < MapRowsDown; ++i) {
			if (MapDownMatrix[i] != nullptr) {
				delete[] MapDownMatrix[i];
				MapDownMatrix[i] = nullptr;
			}
		}
		delete[] MapDownMatrix;
		MapDownMatrix = nullptr;
	}
	if (MapUpMatrix != nullptr) {
		for (int i = 0; i < MapRowsUp; ++i) {
			if (MapUpMatrix[i] != nullptr) {
				delete[] MapUpMatrix[i];
				MapUpMatrix[i] = nullptr;
			}
		}
		delete[] MapUpMatrix;
		MapUpMatrix = nullptr;
	}
	if (ChessDesk != nullptr) {
		delete ChessDesk;
		ChessDesk = nullptr;
	}
}

void Map::MapDisplaierDown(sf::RenderWindow& MainWin)
{
	MapSprite.setTextureRect(TeilsetRects[0].RectPos);
	if (ReadFilePath != "Game\\Texture\\Map\\chess.txt") {
		for (int y = 0; y < MapRowsDown; ++y) {
			for (int x = 0; x < MapColsDown - 1; ++x) {
				MapSprite.setPosition(sf::Vector2f(32 * x, 32 * y));
				MainWin.draw(MapSprite);
			}
		}
	}
	for (int y = 0; y < MapRowsDown; ++y) {
		for (int x = 0; x < MapColsDown - 1; ++x) {
			if (MapDownMatrix[y][x] == 'k') {
				OpenedCaseSprite.setPosition(sf::Vector2f(32 * x, 32 * y));
				MainWin.draw(OpenedCaseSprite);
			}
			else {
				bool temp = false;
				for (int i = 0; i < RectAmount; ++i) {
					if (MapDownMatrix[y][x] == TeilsetRects[i].RectChar) {
						MapSprite.setTextureRect(TeilsetRects[i].RectPos);
						temp = true;
						break;
					}
				}
				if (!temp) {
					MapSprite.setTextureRect(TeilsetRects[RectAmount - 1].RectPos);
				}
				temp = false;
				MapSprite.setPosition(sf::Vector2f(32 * x, 32 * y));
				MainWin.draw(MapSprite);
			}
		}
	}
	if (ReadFilePath == "Game\\Texture\\Map\\chess.txt"){
		ChessDesk->ChessDisplaier(MainWin);
	}
}

void Map::MapDisplaierUp(sf::RenderWindow& MainWin) {
	for (int y = 0; y < MapRowsUp; ++y) {
		for (int x = 0; x < MapColsUp - 1; ++x) {
			bool temp = false;
			for (int i = 0; i < RectAmount; ++i) {
				if (MapUpMatrix[y][x] == TeilsetRects[i].RectChar) {
					MapSprite.setTextureRect(TeilsetRects[i].RectPos);
					temp = true;
					break;
				}
			}
			if (!temp) {
				MapSprite.setTextureRect(TeilsetRects[RectAmount - 1].RectPos);
			}
			temp = false;
			MapSprite.setPosition(sf::Vector2f(32 * x, 32 * y));
			MainWin.draw(MapSprite);
		}
	}
}

int Map::CollisionObjectsDetector(sf::FloatRect* ObjectsCollisionArr)
{
	int index = 0;
	for (int y = 0; y < MapRowsDown; ++y) {
		for (int x = 0; x < MapColsDown - 1; ++x) {
			switch (MapDownMatrix[y][x]) {
				case '5':
				case '6':
				case '7': {
					ObjectsCollisionArr[index] = sf::FloatRect(RectSize.x * x + 12, RectSize.x * y, RectSize.x - 20, RectSize.y - 25);
					index++;
				}; break;
			};
		}
	}
	for (int y = 0; y < MapRowsUp; ++y) {
		for (int x = 0; x < MapColsUp - 1; ++x) {
			switch (MapUpMatrix[y][x]) {
				case '8': {
					if (MapDownMatrix[y + 1][x] != '2' && MapDownMatrix[y + 1][x] != '3' && MapDownMatrix[y + 1][x] != '4') {
						ObjectsCollisionArr[index] = sf::FloatRect(RectSize.x * x + 12, RectSize.x * y + 25, RectSize.x - 20, RectSize.y - 25);
						index++;
					}
				};  break;
				case '9': {
					if (MapDownMatrix[y][x] != '2' && MapDownMatrix[y][x] != '3' && MapDownMatrix[y][x] != '4') {
						ObjectsCollisionArr[index] = sf::FloatRect(RectSize.x * x + 12, RectSize.x * y, RectSize.x - 20, RectSize.y - 25);
						index++;
					}
				};  break;
				case 'a': {
					ObjectsCollisionArr[index] = sf::FloatRect(RectSize.x * x + 25, RectSize.x * y + 12, RectSize.x - 25, RectSize.y - 20);
					index++;
				};  break;
				case 'b': {
					if ((y != 6 || x != 20) && (y != 32 || x != 43)) {
						ObjectsCollisionArr[index] = sf::FloatRect(RectSize.x * x, RectSize.x * y + 12, RectSize.x - 25, RectSize.y - 20);
						index++;
					}
				};  break;
				case 'c':
				case 'd':
				case 'e':
				case 'f': {
					ObjectsCollisionArr[index] = sf::FloatRect(RectSize.x * x, RectSize.x * y, RectSize.x, RectSize.y);
					index++;
				};  break;
				case 'g': {
					ObjectsCollisionArr[index] = sf::FloatRect(RectSize.x * x + 25, RectSize.x * y + 25, RectSize.x - 25, RectSize.y - 25);
					index++;
				}; break;
				case 'j': {
					ObjectsCollisionArr[index] = sf::FloatRect(RectSize.x * x, RectSize.x * y + 25, RectSize.x - 25, RectSize.y - 25);
					index++;
				}; break;
			};
		}
	}
	return index;
}

void Map::ChangeDoorToOpened(sf::FloatRect DoorPos)
{
	if (MapDownMatrix[int(DoorPos.top / 32)][int(DoorPos.left / 32)] == '3') {
		MapDownMatrix[int(DoorPos.top / 32)][int(DoorPos.left / 32)] = '2';
	}
	else if (MapDownMatrix[int(DoorPos.top / 32) + 1][int(DoorPos.left / 32)] == '3') {
		MapDownMatrix[int(DoorPos.top / 32) + 1][int(DoorPos.left / 32)] = '2';
	}
}

void Map::ChangeCaseToOpened(sf::FloatRect CasePos)
{
	MapDownMatrix[(int)CasePos.top / 32][(int)CasePos.left / 32] = 'k';
}

void Map::ChangeSectionToOpen(sf::FloatRect DoorPos)
{
	if (MapDownMatrix[int(DoorPos.top / 32)][int(DoorPos.left / 32)] == '4') {
		MapDownMatrix[int(DoorPos.top / 32)][int(DoorPos.left / 32)] = '2';
	}
	else if (MapDownMatrix[int(DoorPos.top / 32) + 1][int(DoorPos.left / 32)] == '4') {
		MapDownMatrix[int(DoorPos.top / 32) + 1][int(DoorPos.left / 32)] = '2';
	}
}

void Map::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		for (int i = 0; i < 40; ++i) {
			IOFile << MapDownMatrix[i] << std::endl;
		}
	}
	IOFile.close();
}

void Map::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		while (getline(IOFile, temp)) {
			if (counter < 40) {
				for (int i = 0; i < temp.length(); ++i) {
					MapDownMatrix[counter][i] = temp[i];
				}
			}
			counter++;
		}
	}
	IOFile.close();
}