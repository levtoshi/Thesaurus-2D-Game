#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>

namespace fs = std::filesystem;

class RelicShower
{
public:
	sf::Image* RelicImages = nullptr;
	sf::Texture* RelicTextures = nullptr;

	sf::Sprite CurrectSprite;
	sf::RectangleShape HiderShape;

	bool RelicShow = false;
	float RelicShowTime = 1500.f;
	sf::Time RelicShowerTimer = sf::Time::Zero;

	RelicShower();
	~RelicShower();

	void RelicDisplaier(sf::RenderWindow&, int, sf::Vector2f);

	// Save
	std::string SavePath = "Backup\\RelicShower.save";
	std::fstream IOFile;
	void Save();
	void Pull();
};