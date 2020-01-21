#pragma once
#include <SFML/Graphics.hpp>

class EnemyAnimation
{
public:
	sf::IntRect uvRect;
	sf::Vector2u axuCurrentImage;
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime = 0.0f;
	float switchTime = 0.0f;

	EnemyAnimation();
	EnemyAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	EnemyAnimation& operator=(EnemyAnimation& animation2);
	void update(int collum, float deltaTime, unsigned int animationNumber, unsigned int currentSprite);
};

