#pragma once
#include <SFML\Graphics.hpp>

class Plot
{
public:

	// Image & Texture
	sf::Image* PlotImages = nullptr;
	sf::Texture* PlotTextures = nullptr;

	// Background
	sf::Sprite PlotMapSprite;
	sf::Sprite PlotIDLESprite;

	// Main Title
	sf::Font PlotTitleFont;
	sf::Text PlotTitle;

	// Plot text
	sf::Text PlotText;	

	// Back Button
	bool PlotBackButtonHover = false;
	sf::CircleShape PlotBackButton;
	sf::Sprite PlotBackButtonIcon;

	Plot();
	~Plot();

	void PlotDisplaier(sf::RenderWindow&);
	bool PlotControllerMouseMoved(sf::Vector2i mousePos);
	bool PlotControllerMouseClicked(sf::Vector2i mousePos);
};