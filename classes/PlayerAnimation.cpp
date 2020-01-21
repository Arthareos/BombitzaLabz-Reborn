#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation() {}

PlayerAnimation& PlayerAnimation::operator=(PlayerAnimation& other)
{
	m_imageCount = other.m_imageCount;
	m_switchTime = other.m_switchTime;

	m_totalTime = other.m_totalTime;
	m_currentImage.x = other.m_currentImage.x;

	m_uvRect.width = other.m_uvRect.width;
	m_uvRect.height = other.m_uvRect.height;

	return *this;
}

PlayerAnimation::PlayerAnimation(sf::Texture* m_texture, sf::Vector2u m_imageCount, float switchTime)
{
	this->m_imageCount = m_imageCount;
	this->m_switchTime = switchTime;

	m_totalTime = 0.0f;
	m_currentImage.x = 0;
	m_currentImage.y = m_auxCurrentImage.y;
	m_auxCurrentImage.x = 0;

	m_uvRect.width = m_texture->getSize().x / float(m_imageCount.x);
	m_uvRect.height = m_texture->getSize().y / float(m_imageCount.y);
}

void PlayerAnimation::Update(int collum, float deltaTime, unsigned int animationNumber, unsigned int currentSprite)
{
	m_currentImage.x = collum;
	m_totalTime += deltaTime;

	if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;	
		m_currentImage.y++;
	
		if (m_currentImage.y >= (m_auxCurrentImage.y + currentSprite))
		{
			m_currentImage.y = m_auxCurrentImage.y;
		}
	}

	m_uvRect.left = m_currentImage.x * m_uvRect.width;
	m_uvRect.top = m_currentImage.y * m_uvRect.height;
}
