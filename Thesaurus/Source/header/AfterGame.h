#pragma once
#include <SFML\Graphics.hpp>

class AfterGame
{
public:

	sf::Image BackgroundImage;
	sf::Texture BackgroundTexture;
	sf::Sprite BackgroundSprite;
	
	sf::RectangleShape* ButtonsShapes = nullptr;
	sf::Font TextFont;
	sf::Text* ButtonsTexts = nullptr;
	
	sf::Vector2f* TextsPos = nullptr;
	sf::FloatRect* ButtonsRects = nullptr;

	bool AfterGameHovers[3] = {false};

	AfterGame();
	~AfterGame();

	void AfterGameDisplaier(sf::RenderWindow& MainWin);
	bool AfterGameMouseMoved(sf::Vector2i MousePos);
	int AfterGameMouseClicked(sf::Vector2i MousePos);
};