#include "../../header/AfterGame.h"

AfterGame::AfterGame()
{
	BackgroundImage.loadFromFile("Game\\Texture\\Menu\\AfterGame.png");
	BackgroundTexture.loadFromImage(BackgroundImage);
	BackgroundSprite.setTexture(BackgroundTexture);
	BackgroundSprite.setPosition(sf::Vector2f(0.f, 0.f));

	ButtonsRects = new sf::FloatRect[3];
	TextsPos = new sf::Vector2f[3];

	ButtonsShapes = new sf::RectangleShape[3];
	ButtonsTexts = new sf::Text[3];

	TextFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
	ButtonsRects[0] = sf::FloatRect(200, 205, 500, 70);
	ButtonsRects[1] = sf::FloatRect(200, 315, 500, 70);
	ButtonsRects[2] = sf::FloatRect(200, 425, 500, 70);

	TextsPos[0] = sf::Vector2f(332, 218);
	TextsPos[1] = sf::Vector2f(316, 328);
	TextsPos[2] = sf::Vector2f(298, 438);

	sf::String* temp = new sf::String[3]{ L"Продовжити", L"Налаштування", L"Зберегти і вийти" };

	for (int i = 0; i < 3; ++i) {
		ButtonsShapes[i].setOutlineColor(sf::Color::Black);
		ButtonsShapes[i].setOutlineThickness(2.f);
		ButtonsShapes[i].setSize(sf::Vector2f(ButtonsRects[i].width, ButtonsRects[i].height));
		ButtonsShapes[i].setPosition(sf::Vector2f(ButtonsRects[i].left, ButtonsRects[i].top));

		ButtonsTexts[i].setFont(TextFont);
		ButtonsTexts[i].setCharacterSize(36);
		ButtonsTexts[i].setPosition(TextsPos[i]);
		ButtonsTexts[i].setString(temp[i]);
	}

	delete[] temp;
	temp = nullptr;
}

AfterGame::~AfterGame()
{
	if (TextsPos != nullptr) {
		delete[] TextsPos;
		TextsPos = nullptr;
	}
	if (ButtonsRects != nullptr) {
		delete[] ButtonsRects;
		ButtonsRects = nullptr;
	}
	if (ButtonsTexts != nullptr) {
		delete[] ButtonsTexts;
		ButtonsTexts = nullptr;
	}
	if (ButtonsShapes != nullptr) {
		delete[] ButtonsShapes;
		ButtonsShapes = nullptr;
	}
}

void AfterGame::AfterGameDisplaier(sf::RenderWindow& MainWin)
{
	MainWin.draw(BackgroundSprite);

	for (int i = 0; i < 3; ++i) {
		ButtonsShapes[i].setFillColor((AfterGameHovers[i]) ? sf::Color::White : sf::Color::Black);
		ButtonsTexts[i].setFillColor((AfterGameHovers[i]) ? sf::Color::Black : sf::Color::White);
		MainWin.draw(ButtonsShapes[i]);
		MainWin.draw(ButtonsTexts[i]);
	}
}

bool AfterGame::AfterGameMouseMoved(sf::Vector2i MousePos)
{
	for (int i = 0; i < 3; ++i) {
		if (ButtonsRects[i].intersects(sf::FloatRect(MousePos.x, MousePos.y, 1, 1))) {
			AfterGameHovers[i] = true;
		}
		else {
			AfterGameHovers[i] = false;
		}
	}
	return (AfterGameHovers[0] || AfterGameHovers[1] || AfterGameHovers[2]);
}

int AfterGame::AfterGameMouseClicked(sf::Vector2i MousePos)
{
	for (int i = 0; i < 3; ++i) {
		if (ButtonsRects[i].intersects(sf::FloatRect(MousePos.x, MousePos.y, 1, 1))) {
			return i;
		}
	}
	return 3;
}