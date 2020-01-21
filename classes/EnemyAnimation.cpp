#include "EnemyAnimation.h"

EnemyAnimation::EnemyAnimation()
{
}

EnemyAnimation::EnemyAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = axuCurrentImage.y;
	axuCurrentImage.x = 0;
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

}

EnemyAnimation& EnemyAnimation::operator=(EnemyAnimation& animation2)
{
	imageCount = animation2.imageCount;
	switchTime = animation2.switchTime;

	totalTime = animation2.totalTime;
	currentImage.x = animation2.currentImage.x;

	uvRect.width = animation2.uvRect.width;
	uvRect.height = animation2.uvRect.height;

	return *this;
}

void EnemyAnimation::update(int collum, float deltaTime, unsigned int animationNumber, unsigned int currentSprite)
{
	currentImage.x = collum;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.y++;

		if (currentImage.y >= (axuCurrentImage.y + currentSprite))
		{
			currentImage.y = axuCurrentImage.y;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}



