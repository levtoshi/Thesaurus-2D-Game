#pragma once
#include <SFML\Graphics.hpp>

class BeforeGame
{
public:
	sf::Image BackgroundImage;
	sf::Image BackImage;
	sf::Image BackHoverImage;

	sf::Texture BackgroundTexture;
	sf::Texture BackTexture;
	sf::Texture BackHoverTexture;

	sf::Sprite BackgroundSprite;
	sf::Sprite BackSprite;
	sf::CircleShape BackButton;

	sf::RectangleShape PastGameShape;
	sf::RectangleShape NewGameShape;

	sf::FloatRect* BeforeGameRects = nullptr;
	sf::Vector2f* BeforeGameTextPos = nullptr;

	sf::Font TextFont;
	sf::Text PastGameText;
	sf::Text NewGameText;
	
	bool BeforeGameHovers[3] = {false};

	BeforeGame();
	~BeforeGame();

	bool BeforeGameControllerMouseMoved(sf::Vector2i MousePos, bool Backup, bool AfterGame);
	int BeforeGameControllerMouseClicked(sf::Vector2i MousePos, bool Backup, bool AfterGame);
	void BeforeGameDisplaier(sf::RenderWindow& MainWin, bool Backup, bool AfterGame);
};