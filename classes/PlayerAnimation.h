#pragma once
#include <SFML/Graphics.hpp>

class PlayerAnimation {
private:
	sf::Vector2u m_imageCount;
	sf::Vector2u m_currentImage;

	float m_totalTime = 0.0f;
	float m_switchTime = 0.0f;

public :
	PlayerAnimation();
	PlayerAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	PlayerAnimation& operator=(PlayerAnimation& other);

	sf::IntRect m_uvRect;
	sf::Vector2u m_auxCurrentImage;

	void Update(int collum, float deltaTime, unsigned int animationNumber, unsigned int currentSprite);
};

