#include "../../header/BeforeGame.h"

BeforeGame::BeforeGame()
{
	BackgroundImage.loadFromFile("Game\\Texture\\Menu\\BeforeGame.png");
	BackImage.loadFromFile("Game\\Texture\\Menu\\back.png");
	BackHoverImage.loadFromFile("Game\\Texture\\Menu\\back-hover.png");

	BackgroundTexture.loadFromImage(BackgroundImage);
	BackTexture.loadFromImage(BackImage);
	BackHoverTexture.loadFromImage(BackHoverImage);

	BackgroundSprite.setTexture(BackgroundTexture);
	BackgroundSprite.setPosition(sf::Vector2f(0.f, 0.f));
	BackSprite.setTexture(BackTexture);
	BackSprite.setPosition(sf::Vector2f(32.f, 32.f));

	BeforeGameRects = new sf::FloatRect[4];
	BeforeGameRects[0] = sf::FloatRect(20, 20, 50, 50);
	BeforeGameRects[1] = sf::FloatRect(200, 260, 500, 70);
	BeforeGameRects[2] = sf::FloatRect(200, 370, 500, 70);
	BeforeGameRects[3] = sf::FloatRect(200, 315, 500, 70);

	BeforeGameTextPos = new sf::Vector2f[3];
	BeforeGameTextPos[0] = sf::Vector2f(314, 273);
	BeforeGameTextPos[1] = sf::Vector2f(370, 383);
	BeforeGameTextPos[2] = sf::Vector2f(370, 328);

	BackButton.setFillColor(sf::Color::Black);
	BackButton.setOutlineColor(sf::Color::Black);
	BackButton.setOutlineThickness(2.f);
	BackButton.setRadius(25.f);
	BackButton.setPosition(sf::Vector2f(BeforeGameRects[0].left, BeforeGameRects[0].top));

	NewGameShape.setFillColor(sf::Color::Black);
	NewGameShape.setOutlineColor(sf::Color::Black);
	NewGameShape.setOutlineThickness(2.f);
	NewGameShape.setSize(sf::Vector2f(BeforeGameRects[1].width, BeforeGameRects[1].height));

	PastGameShape.setFillColor(sf::Color::Black);
	PastGameShape.setOutlineColor(sf::Color::Black);
	PastGameShape.setOutlineThickness(2.f);
	PastGameShape.setSize(sf::Vector2f(BeforeGameRects[2].width, BeforeGameRects[2].height));
	
	TextFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
	PastGameText.setFont(TextFont);
	PastGameText.setCharacterSize(36);
	PastGameText.setFillColor(sf::Color::White);
	PastGameText.setString(L"Попередня гра");

	NewGameText.setFont(TextFont);
	NewGameText.setCharacterSize(36);
	NewGameText.setFillColor(sf::Color::White);
	NewGameText.setString(L"Нова гра");
}

BeforeGame::~BeforeGame()
{
	if (BeforeGameRects != nullptr) {
		delete[] BeforeGameRects;
		BeforeGameRects = nullptr;
	}
	if (BeforeGameTextPos != nullptr) {
		delete[] BeforeGameTextPos;
		BeforeGameTextPos = nullptr;
	}
}

void BeforeGame::BeforeGameDisplaier(sf::RenderWindow& MainWin, bool Backup, bool AfterGame)
{
	MainWin.draw(BackgroundSprite);

	if (Backup && !AfterGame) {
		PastGameShape.setFillColor((BeforeGameHovers[1]) ? sf::Color::White : sf::Color::Black);
		PastGameText.setFillColor((BeforeGameHovers[1]) ? sf::Color::Black : sf::Color::White);

		NewGameShape.setFillColor((BeforeGameHovers[2]) ? sf::Color::White : sf::Color::Black);
		NewGameText.setFillColor((BeforeGameHovers[2]) ? sf::Color::Black : sf::Color::White);

		PastGameShape.setPosition(BeforeGameRects[1].left, BeforeGameRects[1].top);
		NewGameShape.setPosition(BeforeGameRects[2].left, BeforeGameRects[2].top);

		PastGameText.setPosition(BeforeGameTextPos[0]);
		NewGameText.setPosition(BeforeGameTextPos[1]);

		MainWin.draw(PastGameShape);
		MainWin.draw(NewGameShape);
		MainWin.draw(PastGameText);
		MainWin.draw(NewGameText);
	}
	else {
		NewGameShape.setFillColor((BeforeGameHovers[2]) ? sf::Color::White : sf::Color::Black);
		NewGameText.setFillColor((BeforeGameHovers[2]) ? sf::Color::Black : sf::Color::White);

		NewGameShape.setPosition(BeforeGameRects[3].left, BeforeGameRects[3].top);

		NewGameText.setPosition(BeforeGameTextPos[2]);

		MainWin.draw(NewGameShape);
		MainWin.draw(NewGameText);
	}

	BackButton.setFillColor((BeforeGameHovers[0]) ? sf::Color::White : sf::Color::Black);
	BackSprite.setTexture((BeforeGameHovers[0]) ? BackHoverTexture : BackTexture);
	MainWin.draw(BackButton);
	MainWin.draw(BackSprite);
}

bool BeforeGame::BeforeGameControllerMouseMoved(sf::Vector2i MousePos, bool Backup, bool AfterGame)
{
	if (Backup && !AfterGame) {
		for (int i = 0; i < 3; ++i) {
			if (BeforeGameRects[i].intersects(sf::FloatRect(MousePos.x, MousePos.y, 1, 1))) {
				BeforeGameHovers[i] = true;
			}
			else {
				BeforeGameHovers[i] = false;
			}
		}
	}
	else {
		if (BeforeGameRects[0].intersects(sf::FloatRect(MousePos.x, MousePos.y, 1, 1))) {
			BeforeGameHovers[0] = true;
		}
		else {
			BeforeGameHovers[0] = false;
		}

		if (BeforeGameRects[3].intersects(sf::FloatRect(MousePos.x, MousePos.y, 1, 1))) {
			BeforeGameHovers[2] = true;
		}
		else {
			BeforeGameHovers[2] = false;
		}
	}
	
	return (BeforeGameHovers[0] || BeforeGameHovers[1] || BeforeGameHovers[2]);
}

int BeforeGame::BeforeGameControllerMouseClicked(sf::Vector2i MousePos, bool Backup, bool AfterGame)
{
	if (Backup && !AfterGame) {
		for (int i = 0; i < 3; ++i) {
			if (BeforeGameRects[i].intersects(sf::FloatRect(MousePos.x, MousePos.y, 1, 1))) {
				return i;
			}
		}
	}
	else {
		if (BeforeGameRects[0].intersects(sf::FloatRect(MousePos.x, MousePos.y, 1, 1))) {
			return 0;
		}
		else if (BeforeGameRects[3].intersects(sf::FloatRect(MousePos.x, MousePos.y, 1, 1))) {
			return 2;
		}
	}
	return 3;
}