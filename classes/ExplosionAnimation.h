#pragma once

#include <SFML/Graphics.hpp>

class ExplosionAnimation
{
private:
	sf::Vector2u exA_imageCount;
	sf::Vector2u exA_currentImage;

	float totalTime;
	float switchTime;

public:
	sf::IntRect exA_uvRect;

public:
	ExplosionAnimation();
	ExplosionAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

	void update();
};

