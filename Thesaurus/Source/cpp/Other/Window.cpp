#include "../../header/Window.h"

Window::Window()
{
	WindowObject.create(sf::VideoMode(WinSize.x, WinSize.y), title);
	WindowObject.setFramerateLimit(60);
}

Window::~Window()
{
}