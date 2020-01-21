#include "Explosion.h"

Explosion::Explosion() {}

Explosion::Explosion(std::string imageDirectory, sf::Vector2u imageCount)
{
	this->imageCount = imageCount;
	explosionSize = 2;

	if (!texture.loadFromFile(imageDirectory))
	{
		std::cout << " +> [ERROR] Explosion image not loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Explosion image loaded;" << std::endl;
	}

	sprExplosion.setTexture(&texture);

	e_uvRect.width = texture.getSize().x / float(imageCount.x);
	e_uvRect.height = texture.getSize().y / float(imageCount.y);
	currentImage.x = 0;

	while (currentImage.x < this->imageCount.x)
	{
		e_uvRect.left = currentImage.x * e_uvRect.width;
		e_uvRect.top = currentImage.y * e_uvRect.height;
		sprExplosion.setTextureRect(e_uvRect);


		explVec.emplace_back(sprExplosion);


		currentImage.x++;
	}
}

int Explosion::getExplosionSize()
{
	return explosionSize;
}

void Explosion::setExplosionSize(uint16_t size)
{
	this->explosionSize = size;
}
