#include "Explosion.h"

Explosion::Explosion() {}

Explosion::Explosion(std::string imageDirectory, sf::Vector2u imageCount)
{
	this->m_imageCount = imageCount;
	m_explosionSize = 1;

	if (!m_texture.loadFromFile(imageDirectory))
	{
		std::cout << " +> [ERROR] Explosion image not loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Explosion image loaded;" << std::endl;
	}

	m_sprite.setTexture(&m_texture);

	e_uvRect.width = m_texture.getSize().x / float(imageCount.x);
	e_uvRect.height = m_texture.getSize().y / float(imageCount.y);
	m_currentImage.x = 0;

	while (m_currentImage.x < this->m_imageCount.x)
	{
		e_uvRect.left = m_currentImage.x * e_uvRect.width;
		e_uvRect.top = m_currentImage.y * e_uvRect.height;
		m_sprite.setTextureRect(e_uvRect);

		m_explosionsVector.emplace_back(m_sprite);
		m_currentImage.x++;
	}
}

Explosion::~Explosion() {}

const uint16_t& Explosion::GetExplosionSize()
{
	return m_explosionSize;
}

std::vector<sf::RectangleShape>& Explosion::GetExplosionsVector()
{
	return m_explosionsVector;
}

void Explosion::SetExplosionSize(uint16_t size)
{
	this->m_explosionSize = size;
}
