#pragma once
#include <SFML/Graphics.hpp>

class EnemyAnimation
{
public:
	sf::IntRect uvRect;
	sf::Vector2u axuCurrentImage;
	sf::Vector2u m_imageCount;
	sf::Vector2u m_currentImage;
	float totalTime = 0.0f;
	float switchTime = 0.0f;

	EnemyAnimation();
	EnemyAnimation(sf::Texture* m_texture, sf::Vector2u m_imageCount, float switchTime);
	EnemyAnimation& operator=(EnemyAnimation& animation2);
	void update(int collum, float deltaTime, unsigned int animationNumber, unsigned int currentSprite);
};

