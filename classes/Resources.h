#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <iostream>

class Text {
private:
	sf::Font font;
	sf::Text text;

public:
	Text();
	sf::Text& getText();
};