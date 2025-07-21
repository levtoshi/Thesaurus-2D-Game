#include "../../header/Chess.h"

Chess::Chess()
{
	ChessElementsImage.loadFromFile("Game\\Texture\\Map\\chess-texture.png");
	ChessDeskImage.loadFromFile("Game\\Texture\\Map\\chess-desk.jpg");

	ChessElementsTexture.loadFromImage(ChessElementsImage);
	ChessDeskTexture.loadFromImage(ChessDeskImage);
	
	ChessDeskSprite.setTexture(ChessDeskTexture);
	ChessDeskSprite.setScale((256.f / 4096.f), (256.f / 4096.f));
	ChessElementsSprite.setTexture(ChessElementsTexture);
	ChessElementsSprite.setScale((192.f / 1344.f), (64.f / 449.f));
}

Chess::~Chess()
{
}

void Chess::ChessDisplaier(sf::RenderWindow& MainWin)
{
	// Desk
	ChessDeskSprite.setPosition(sf::Vector2f(64, 96));
	MainWin.draw(ChessDeskSprite);

	// White
	ChessElementsSprite.setTextureRect(sf::IntRect(0, 0, 224, 224));
	for (int i = 0; i < 8; ++i) {
		ChessElementsSprite.setPosition(sf::Vector2f(64 + i * 32, 288));
		MainWin.draw(ChessElementsSprite);
	}

	ChessElementsSprite.setTextureRect(sf::IntRect(224, 0, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(98, 320));
	MainWin.draw(ChessElementsSprite);
	ChessElementsSprite.setPosition(sf::Vector2f(258, 320));
	MainWin.draw(ChessElementsSprite);

	ChessElementsSprite.setTextureRect(sf::IntRect(448, 0, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(129, 320));
	MainWin.draw(ChessElementsSprite);
	ChessElementsSprite.setPosition(sf::Vector2f(226, 320));
	MainWin.draw(ChessElementsSprite);

	ChessElementsSprite.setTextureRect(sf::IntRect(672, 0, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(66, 320));
	MainWin.draw(ChessElementsSprite);
	ChessElementsSprite.setPosition(sf::Vector2f(291, 320));
	MainWin.draw(ChessElementsSprite);

	ChessElementsSprite.setTextureRect(sf::IntRect(896, 0, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(194, 320));
	MainWin.draw(ChessElementsSprite);

	ChessElementsSprite.setTextureRect(sf::IntRect(1120, 0, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(160, 320));
	MainWin.draw(ChessElementsSprite);

	// Black
	ChessElementsSprite.setTextureRect(sf::IntRect(0, 224, 224, 224));
	for (int i = 0; i < 8; ++i) {
		ChessElementsSprite.setPosition(sf::Vector2f(64 + i * 32, 128));
		MainWin.draw(ChessElementsSprite);
	}

	ChessElementsSprite.setTextureRect(sf::IntRect(224, 224, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(98, 96));
	MainWin.draw(ChessElementsSprite);
	ChessElementsSprite.setPosition(sf::Vector2f(258, 96));
	MainWin.draw(ChessElementsSprite);

	ChessElementsSprite.setTextureRect(sf::IntRect(448, 224, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(129, 96));
	MainWin.draw(ChessElementsSprite);
	ChessElementsSprite.setPosition(sf::Vector2f(226, 96));
	MainWin.draw(ChessElementsSprite);

	ChessElementsSprite.setTextureRect(sf::IntRect(672, 224, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(66, 96));
	MainWin.draw(ChessElementsSprite);
	ChessElementsSprite.setPosition(sf::Vector2f(291, 96));
	MainWin.draw(ChessElementsSprite);

	ChessElementsSprite.setTextureRect(sf::IntRect(896, 224, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(194, 96));
	MainWin.draw(ChessElementsSprite);

	ChessElementsSprite.setTextureRect(sf::IntRect(1120, 224, 224, 224));
	ChessElementsSprite.setPosition(sf::Vector2f(160, 96));
	MainWin.draw(ChessElementsSprite);
}