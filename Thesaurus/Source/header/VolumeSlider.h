#pragma once
#include <SFML/Graphics.hpp>

class VolumeSlider
{
public:
	sf::Image SliderBaseImage;
	sf::Image SliderGoImage;

	sf::Texture SliderBaseTexture;
	sf::Texture SliderGoTexture;

	sf::Sprite SliderBaseSprite;
	sf::Sprite SliderGoSprite;

	sf::Vector2f SliderGoPos;
	sf::IntRect SliderActiveZone;

	VolumeSlider();
	~VolumeSlider();

	bool SliderClick(sf::Vector2i, float&);
	void SliderDisplaier(sf::RenderWindow&);
	bool SliderMouseMoved(sf::Vector2i);
};