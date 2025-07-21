#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

namespace fs = std::filesystem;

class Password
{
public:
	sf::Image TeilsetImage;
	sf::Image DoorImage;
	sf::Image DoorWrongImage;

	sf::Texture TeilsetTexture;
	sf::Texture DoorTexture;
	sf::Texture DoorWrongTexture;

	sf::Sprite TeilsetSprite;
	sf::Sprite DoorSprite;

	std::string TeilsetPath;

	std::string PasswordValue;

	sf::FloatRect* WallNumbersPos = nullptr;
	sf::Font TextFont;
	sf::Text EnteredText;
	sf::String EnteredPassword = "";

	Password(sf::FloatRect*);
	~Password();

	void PasswordWallDisplaier(sf::RenderWindow&);

	int PasswordWindowController(sf::RenderWindow&, char);
	void PasswordWindowDisplaier(sf::RenderWindow&);

	// Save
	std::string SavePath = "Backup\\Password.save";
	std::fstream IOFile;
	void Save();
	void Pull();
};