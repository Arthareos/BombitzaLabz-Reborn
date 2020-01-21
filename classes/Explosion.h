#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Map.h"

class Explosion {
private:
	sf::RectangleShape m_sprite;
	sf::Texture m_texture;
	sf::Vector2u m_imageCount;
	sf::Vector2u m_currentImage;

	uint16_t m_explosionSize;

	std::vector<sf::RectangleShape> m_explosionsVector;
	sf::IntRect e_uvRect;

public:
	Explosion();
	Explosion(std::string imageDirectory, sf::Vector2u m_imageCount);
	~Explosion();

	const uint16_t& GetExplosionSize();
	std::vector<sf::RectangleShape>& GetExplosionsVector();

	void SetExplosionSize(uint16_t size);
};

