#include "../../header/VolumeSlider.h"

VolumeSlider::VolumeSlider()
{
	SliderBaseImage.loadFromFile("Game\\Texture\\Menu\\SliderBase.png");
	SliderGoImage.loadFromFile("Game\\Texture\\Menu\\SliderGo.png");

	SliderBaseTexture.loadFromImage(SliderBaseImage);
	SliderGoTexture.loadFromImage(SliderGoImage);

	SliderBaseSprite.setTexture(SliderBaseTexture);
	SliderGoSprite.setTexture(SliderGoTexture);

	SliderBaseSprite.setPosition(sf::Vector2f(258, 574));
	SliderGoSprite.setPosition(sf::Vector2f(305, 568));

	SliderActiveZone = sf::IntRect(258, 568, 100, 15);
}

VolumeSlider::~VolumeSlider()
{
}


bool VolumeSlider::SliderClick(sf::Vector2i MousePos, float& MainVolume)
{
	if (SliderActiveZone.intersects(sf::IntRect(MousePos.x, MousePos.y, 1, 1))) {
		SliderGoSprite.setPosition(sf::Vector2f(258 + (MousePos.x - SliderActiveZone.left), 568));
		MainVolume = ((MousePos.x - SliderActiveZone.left) / (float)SliderBaseTexture.getSize().x);
		return true;
	}
	return false;
}

void VolumeSlider::SliderDisplaier(sf::RenderWindow& MainWin)
{
	MainWin.draw(SliderBaseSprite);
	MainWin.draw(SliderGoSprite);
}

bool VolumeSlider::SliderMouseMoved(sf::Vector2i mousePos)
{
	if (SliderActiveZone.intersects(sf::IntRect(mousePos.x, mousePos.y, 1, 1))) {
		return true;
	}
	return false;
}