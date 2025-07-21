#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

class Keys
{
public:
	sf::Image KeyImage;
	sf::Texture KeyTexture;
	sf::Sprite KeySprite;
	sf::Vector2f KeySpriteSize;

	int KeysLocationsSize = 0;
	sf::FloatRect* KeysLocations = nullptr;

	Keys(sf::FloatRect*, int);
	~Keys();

	int KeysController(sf::FloatRect HeroLocation, bool);
	void KeysDisplaier(sf::RenderWindow&, sf::FloatRect);	
	void KeyDelete(int);

	// Save
	std::string SavePath = "Backup\\Keys.save";
	std::fstream IOFile;
	void Save();
	void Pull();
};