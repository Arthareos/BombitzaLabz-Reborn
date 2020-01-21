#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Crate {
private:
	std::pair <float_t, float_t> coordinates;
	sf::Sprite sprite;
	sf::Texture texture;

	bool hasExit;
	bool hasKey;
	bool hasPowerUp;

public:
	Crate(bool hasExit, bool hasKey, bool hasPowerUp);

	void setCoordinates(float_t x, float_t y);
	void setTexture(std::string textureDirectory);

	std::pair <float_t, float_t> getCoordinates();
	sf::Sprite& getSprite();
};