#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

struct MenuText {
	sf::Text Text;
	sf::Color TextColor = sf::Color::White;
	sf::Font TextFont;
	sf::Vector2f TextPos;
	sf::String TextTitle = L"None";
	int TextSize = 36;
};

struct MenuButton {
	sf::RectangleShape ButtonRect;
	MenuText ButtonText;

	sf::Vector2f ButtonPos;
	sf::Vector2f ButtonSize = sf::Vector2f(250, 75);

	float ButtonCornerRadius = 10.0f;
	sf::Color ButtonFillColor = sf::Color::Black;
	sf::Color ButtonOutColor = sf::Color::Black;
	float ButtonOutThick = 2.f;
};


class Menu
{
public:
	
	// Images & Textures
	sf::Image* MenuImages = nullptr;
	sf::Texture* MenuTextures = nullptr;

	// Background
	sf::Sprite MenuCastleSprite;
	sf::Sprite MenuIDLESprite;

	// Settings button
	sf::Sprite MenuSettingsButtonIcon;
	sf::CircleShape MenuSettingsButton;

	// Buttons
	MenuButton* Buttons = nullptr;

	// Main title
	MenuText MenuTitle;

	// Hover buttons
	bool HoverButtonsStates[4] = {false};

	Menu();
	~Menu();

	void MenuDisplaier(sf::RenderWindow&);

	bool MenuControllerMouseMoved(sf::Vector2i);
	int MenuControllerMouseClicked(sf::Vector2i);

	void MenuButtonStart(MenuButton&);
	void MenuTextStart(MenuText&);
};