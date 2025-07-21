#pragma once
#include <SFML\Graphics.hpp>

class Chess
{
public:
	sf::Image ChessElementsImage;
	sf::Image ChessDeskImage;

	sf::Texture ChessElementsTexture;
	sf::Texture ChessDeskTexture;

	sf::Sprite ChessElementsSprite;
	sf::Sprite ChessDeskSprite;

	Chess();
	~Chess();

	void ChessDisplaier(sf::RenderWindow&);
};