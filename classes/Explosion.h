#pragma once
#include <SFML\Graphics.hpp>

#include <iostream>


#include "Player.h"
#include "Map.h"

class Explosion{
private:
	sf::RectangleShape sprExplosion;
	
	sf::Texture texture;
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	unsigned int explosionSize;


public:
	sf::IntRect e_uvRect;
	std::vector<sf::RectangleShape> explVec;

	Explosion();
	Explosion(std::string imageDirectory, sf::Vector2u imageCount);

	int getExplosionSize();
	void setExplosionSize(uint16_t size);

};

