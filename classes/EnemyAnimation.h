#pragma once
#include <SFML/Graphics.hpp>

class EnemyAnimation {
private:
	sf::Vector2u m_imageCount;
	sf::Vector2u m_currentImage;

	float m_totalTime = 0.0f;
	float m_switchTime = 0.0f;

public:
	EnemyAnimation();
	EnemyAnimation(sf::Texture* m_texture, sf::Vector2u m_imageCount, float switchTime);
	EnemyAnimation& operator=(EnemyAnimation& other);

	sf::IntRect m_uvRect;
	sf::Vector2u m_auxCurrentImage;

	void Update(int collum, float deltaTime, unsigned int animationNumber, unsigned int currentSprite);
};

