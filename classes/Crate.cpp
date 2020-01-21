#include "Crate.h"

Crate::Crate(bool hasExit, bool hasKey, bool hasPowerUp)
{
	this->hasExit = hasExit;
	this->hasKey = hasKey;
	this->hasPowerUp = hasPowerUp;

	this->sprite.setScale(1, 1);
}

//first -> x, second -> y
void Crate::setCoordinates(float_t x, float_t y)
{
	coordinates.first = x;
	coordinates.second = y;
}

void Crate::setTexture(std::string textureDirectory)
{
	if (!m_texture.loadFromFile(textureDirectory))
	{
		std::cout << " +> [ERROR] Tile texture not loaded;" << std::endl;
	}

	sprite.setTexture(m_texture);
	sprite.setScale(1, 1);
}

std::pair <float_t, float_t> Crate::getCoordinates()
{
	return this->coordinates;
}

sf::Sprite& Crate::getSprite()
{
	return this->sprite;
}