#include "EnemyAnimation.h"

EnemyAnimation::EnemyAnimation()
{
}

EnemyAnimation::EnemyAnimation(sf::Texture* m_texture, sf::Vector2u m_imageCount, float switchTime)
{
	this->m_imageCount = m_imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	m_currentImage.x = 0;
	m_currentImage.y = axuCurrentImage.y;
	axuCurrentImage.x = 0;
	uvRect.width = m_texture->getSize().x / float(m_imageCount.x);
	uvRect.height = m_texture->getSize().y / float(m_imageCount.y);

}

EnemyAnimation& EnemyAnimation::operator=(EnemyAnimation& animation2)
{
	m_imageCount = animation2.m_imageCount;
	switchTime = animation2.switchTime;

	totalTime = animation2.totalTime;
	m_currentImage.x = animation2.m_currentImage.x;

	uvRect.width = animation2.uvRect.width;
	uvRect.height = animation2.uvRect.height;

	return *this;
}

void EnemyAnimation::update(int collum, float deltaTime, unsigned int animationNumber, unsigned int currentSprite)
{
	m_currentImage.x = collum;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		m_currentImage.y++;

		if (m_currentImage.y >= (axuCurrentImage.y + currentSprite))
		{
			m_currentImage.y = axuCurrentImage.y;
		}
	}

	uvRect.left = m_currentImage.x * uvRect.width;
	uvRect.top = m_currentImage.y * uvRect.height;
}



