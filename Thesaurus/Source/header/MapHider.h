#pragma once
#include <SFML\Graphics.hpp>

class MapHider
{
public:
	sf::RectangleShape* HidersShapes = nullptr;
	sf::FloatRect* HidersPositions = nullptr;

	MapHider();
	~MapHider();

	void HiderDislaier(sf::RenderWindow&, int);
};