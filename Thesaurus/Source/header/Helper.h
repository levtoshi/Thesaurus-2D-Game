#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

class Helper
{
public:
	sf::Image* DoorStatusImages = nullptr;
	sf::Image* RelicsImages = nullptr;
	sf::Image* HelpImages = nullptr;
	sf::Image ArrowImage;
	sf::Image KeyImage;

	sf::Texture* DoorStatusTextures = nullptr;
	sf::Texture* RelicsTextures = nullptr;
	sf::Texture* HelpTextures = nullptr;
	sf::Texture ArrowTexture;
	sf::Texture KeyTexture;

	sf::Sprite* DoorStatusSprites = nullptr;
	sf::Sprite* RelicsSprites = nullptr;
	sf::Sprite* HelpSprites = nullptr;
	sf::Sprite* ArrowsSprites = nullptr;
	sf::Sprite* KeysSprites = nullptr;

	sf::Vector2f HelpSpriteSize;

	// Temporary info savers
	int tempMode;
	sf::FloatRect tempPosition;
	bool FPSChange = false;

	Helper();
	~Helper();

	void HelperStaticDisplaier(sf::RenderWindow&, int, int, sf::Vector2f, sf::Vector2f);
	void HelperArrowsDisplaier(sf::RenderWindow&);
	void HelperTempDisplaier(sf::RenderWindow&, int, sf::FloatRect);

	// Save
	std::string SavePath = "Backup\\Helper.save";
	std::fstream IOFile;
	void Save();
	void Pull();
};