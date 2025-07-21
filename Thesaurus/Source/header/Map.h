#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "Chess.h"

namespace fs = std::filesystem;

struct MapRectInfo {
	char RectChar;
	sf::IntRect RectPos;
};

class Map
{
public:
	sf::Image MapImage;
	sf::Image OpenedCaseImage;

	sf::Texture MapTexture;
	sf::Texture OpenedCaseTexture;

	sf::Sprite MapSprite;
	sf::Sprite OpenedCaseSprite;

	std::string ReadFilePath;
	std::ifstream ReadFile;

	std::string MapTeilsetPath;
	int MapRowsDown, MapRowsUp;
	int MapColsDown, MapColsUp;
	sf::Vector2f RectSize;
	int RectAmount;
	MapRectInfo* TeilsetRects;

	sf::Vector2f MapSize;
	Chess* ChessDesk;

	unsigned char** MapDownMatrix = nullptr;
	unsigned char** MapUpMatrix = nullptr;

	Map(std::string);
	~Map();
	
	void MapDisplaierDown(sf::RenderWindow&);
	void MapDisplaierUp(sf::RenderWindow&);
	int CollisionObjectsDetector(sf::FloatRect*);

	void ChangeDoorToOpened(sf::FloatRect);
	void ChangeCaseToOpened(sf::FloatRect);
	void ChangeSectionToOpen(sf::FloatRect);

	// Save
	std::string SavePath = "Backup\\Map.save";
	std::fstream IOFile;
	void Save();
	void Pull();
};