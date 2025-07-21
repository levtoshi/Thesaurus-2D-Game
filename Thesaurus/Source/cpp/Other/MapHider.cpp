#include "../../header/MapHider.h"

MapHider::MapHider()
{
	HidersPositions = new sf::FloatRect[7];
	HidersPositions[0] = sf::FloatRect(0, 384, 640, 448);
	HidersPositions[1] = sf::FloatRect(0, 0, 640, 384);
	HidersPositions[2] = sf::FloatRect(640, 0, 736, 384);
	HidersPositions[3] = sf::FloatRect(640, 384, 736, 448);
	HidersPositions[4] = sf::FloatRect(640, 832, 736, 448);
	HidersPositions[5] = sf::FloatRect(1376, 384, 544, 896);
	HidersPositions[6] = sf::FloatRect(1376, 0, 544, 384);

	HidersShapes = new sf::RectangleShape[7];
	for (int i = 0; i < 7; ++i) {
		HidersShapes[i].setFillColor(sf::Color(0, 0, 0, 128));
		HidersShapes[i].setPosition(sf::Vector2f(HidersPositions[i].left, HidersPositions[i].top));
		HidersShapes[i].setSize(sf::Vector2f(HidersPositions[i].width, HidersPositions[i].height));
	}
}

MapHider::~MapHider()
{
	if (HidersShapes != nullptr) {
		delete[] HidersShapes;
		HidersShapes = nullptr;
	}
	if (HidersPositions != nullptr) {
		delete[] HidersPositions;
		HidersPositions = nullptr;
	}
}

void MapHider::HiderDislaier(sf::RenderWindow& MainWin, int CurrentSection)
{
	for (int i = (CurrentSection); i < 7; ++i) {
		MainWin.draw(HidersShapes[i]);
	}
}