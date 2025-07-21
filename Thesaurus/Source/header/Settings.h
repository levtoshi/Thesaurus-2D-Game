#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "VolumeSlider.h"
#include "FonMusic.h"

struct SettingsText {
	sf::Text Text;
	sf::Vector2f TextPos;
	sf::Color TextColor = sf::Color::Black;
	sf::Font TextFont;
	sf::String TextTitle = L"None";
	int TextSize = 15;
};

struct SettingsField {
	sf::RectangleShape FieldRect;
	SettingsText FieldText;

	sf::Vector2f FieldPos;
	sf::Vector2f FieldSize = sf::Vector2f(350, 50);

	float FieldCornerRadius = 10.f;
	sf::Color FieldFillColor = sf::Color::White;
	sf::Color FieldOutColor = sf::Color::Black;
	float FieldOutThick = 2.f;

	sf::Color LinkerHoverFillColor = sf::Color(225, 225, 225);
};

struct SettingsTicker {
	sf::CircleShape TickerShape;
	sf::Vector2f TickerPos;
	float TickerRadius = 10.f;
	sf::Color TickerFillColor = sf::Color::White;
	sf::Color TickerOutColor = sf::Color::Black;
	float TickerOutThick = 2.f;
	
	// Hover
	bool TickerHover = false;
	sf::Color TickerHoverFillColor = sf::Color(225, 225, 225);
	
	// Active
	bool TickerActive = true;
};

class Settings
{
public:
	int GOTO;

	// Images & Textures
	sf::Image* SettingsImages = nullptr;
	sf::Texture* SettingsTextures = nullptr;

	// Background
	sf::Sprite SettingsBackgroundSprite;
	sf::Sprite SettingsIconSprite;

	// Fields
	SettingsField* FieldsArray = nullptr;
	VolumeSlider* SliderObject = nullptr;

	// Tickers
	SettingsTicker* TickersArray = nullptr;
	sf::Sprite* TickersSpritesArray = nullptr;

	// Main Title
	SettingsText SettingsTitle;

	// Back button
	bool SettingsBackButtonHover = false;
	sf::CircleShape SettingsBackButton;
	sf::Sprite SettingsBackButtonIcon;

	// Linkers hover state
	bool LinkersHoverStates[2] = {false};
	bool LinkersActiveStates[2] = { false };

	Settings();
	~Settings();
	
	void SettingsDisplaier(sf::RenderWindow&);
	bool SettingsControllerMouseMoved(sf::Vector2i);
	bool SettingsControllerMouseClicked(sf::Vector2i, bool&, bool&, FonMusic&, FonMusic&);

	// Setup Frontend
	void SettingsFieldStart(SettingsField&);
	void SettingsTickerStart(SettingsTicker&);
	void SettingsTextStart(SettingsText&);
};