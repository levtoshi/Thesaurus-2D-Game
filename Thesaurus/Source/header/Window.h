#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Window
{
public:
	sf::RenderWindow WindowObject;
	std::string title = "Thesaurus";
	sf::Vector2f WinSize = sf::Vector2f(900, 700);
	Window();
	~Window();
};