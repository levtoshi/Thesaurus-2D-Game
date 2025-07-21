#include "../../header/Plot.h"

Plot::Plot()
{
	PlotImages = new sf::Image[4];
	PlotTextures = new sf::Texture[4];

	PlotImages[0].loadFromFile("Game\\Texture\\Menu\\IDLE.png");
	PlotImages[1].loadFromFile("Game\\Texture\\Menu\\MapPlot.png");
	PlotImages[2].loadFromFile("Game\\Texture\\Menu\\back.png");
	PlotImages[3].loadFromFile("Game\\Texture\\Menu\\back-hover.png");

	for (int i = 0; i < 4; ++i) {
		PlotTextures[i].loadFromImage(PlotImages[i]);
	}

	PlotMapSprite.setTexture(PlotTextures[1]);
	PlotIDLESprite.setTexture(PlotTextures[0]);

	PlotMapSprite.setPosition(400, 0);
	PlotIDLESprite.setPosition(550, 254);

	// Main Title
	PlotTitleFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
	PlotTitle.setFont(PlotTitleFont);
	PlotTitle.setFillColor(sf::Color::Black);
	PlotTitle.setCharacterSize(36);
	PlotTitle.setStyle(sf::Text::Bold);
	PlotTitle.setPosition(sf::Vector2f(135, 70));
	PlotTitle.setString(L"�����");

	// Plot Text
	PlotText.setFont(PlotTitleFont);
	PlotText.setFillColor(sf::Color::Black);
	PlotText.setCharacterSize(14);
	PlotText.setPosition(sf::Vector2f(40, 138));
	PlotText.setString(L"��䳿 ����������� � ������� �����. \n�������� ����� � ������ ������� �����\n\n���� ����� ���������� �� 7 ������, ��\n������� �� ����� ���� �� �����. � �������\n������ � ��������. ������ ���������� ��\n������ �'����� �������� ���������\n\n� ����� ������ � ������ � ���⳺�, ���\n�������� ������� ���� �� ��������\n������. � ��� ����, ��� ������� ���� �� 1\n�� 2 �������� ����� ������ 1 ������, � ����\n����� ������� ���� �� 2 �� 3 ��������, \n��� ������ ����⳿ � 1 �� 2 ������.\n³������� ��� ����, ��� ������� ������\n���� �� ������ ����� ���� 7 ������\n\n��� ����, ��� ������� ������ � ������� �\n����� ������ ����� ������ 3 �����. ϳ���\n����, �� ����������� ������ � �������, \n����� ���� ������� ���� ������ ����\n�����\'� ��� ������ � �����\n\n���� ���������� ��� ������� �� 7\n������, ��� ��� ����, ��� ������� ������\n���� �� ������ ����� �� ������ ������\n\nϳ������� : ������ ����� � ������� ��\n�������");

	// Back button
	PlotBackButtonIcon.setTexture(PlotTextures[2]);
	PlotBackButtonIcon.setPosition(sf::Vector2f(32, 32));

	PlotBackButton.setFillColor(sf::Color::Black);
	PlotBackButton.setOutlineColor(sf::Color::Black);
	PlotBackButton.setOutlineThickness(2.f);
	PlotBackButton.setRadius(25.f);
	PlotBackButton.setPosition(sf::Vector2f(20, 20));
}

Plot::~Plot()
{
	if (PlotImages != nullptr) {
		delete[] PlotImages;
		PlotImages = nullptr;
	}
	if (PlotTextures != nullptr) {
		delete[] PlotTextures;
		PlotTextures = nullptr;
	}
}

void Plot::PlotDisplaier(sf::RenderWindow& MainWin)
{
	MainWin.clear(sf::Color::White);
	MainWin.draw(PlotMapSprite);
	MainWin.draw(PlotIDLESprite);

	MainWin.draw(PlotTitle);
	MainWin.draw(PlotText);

	PlotBackButton.setFillColor((PlotBackButtonHover) ? sf::Color::White : sf::Color::Black);
	PlotBackButtonIcon.setTexture((PlotBackButtonHover) ? PlotTextures[3] : PlotTextures[2]);
	MainWin.draw(PlotBackButton);
	MainWin.draw(PlotBackButtonIcon);
}

bool Plot::PlotControllerMouseMoved(sf::Vector2i mousePos)
{
	if (mousePos.x > PlotBackButton.getPosition().x && mousePos.x < (PlotBackButton.getPosition().x + PlotBackButton.getRadius() * 2) &&
		mousePos.y > PlotBackButton.getPosition().y && mousePos.y < (PlotBackButton.getPosition().y + PlotBackButton.getRadius() * 2)) {
		PlotBackButtonHover = true;
	}
	else {
		PlotBackButtonHover = false;
	}
	return PlotBackButtonHover;
}

bool Plot::PlotControllerMouseClicked(sf::Vector2i mousePos)
{
	if (mousePos.x > PlotBackButton.getPosition().x && mousePos.x < (PlotBackButton.getPosition().x + PlotBackButton.getRadius() * 2) &&
		mousePos.y > PlotBackButton.getPosition().y && mousePos.y < (PlotBackButton.getPosition().y + PlotBackButton.getRadius() * 2)) {
		return true;
	}
	else {
		return false;
	}
}