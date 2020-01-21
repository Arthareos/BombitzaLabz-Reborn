#include "Resources.h"

Text::Text()
{
	if (!font.loadFromFile(".\\resources\\font.ttf"))
	{
		std::cout << " +> [ERROR] Text font NOT loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Text font loaded successfully;" << std::endl;
	}

	text.setFont(font);
	text.setCharacterSize(24);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
}

sf::Text& Text::getText()
{
	return text;
}
