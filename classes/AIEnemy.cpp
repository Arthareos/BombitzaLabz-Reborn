#include "AIEnemy.h"
#include <time.h>
#include <string>

AIEnemy::AIEnemy(std::string imageDirectory, sf::Vector2u m_imageCount, float switchTime, float speed)
{
	if (!enemy_texture.loadFromFile(imageDirectory))
	{
		std::cout << " +> [ERROR] Enemy texture NOT loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Enemy texture loaded;" << std::endl;

		m_sprite.setTexture(&enemy_texture);
	}

	EnemyAnimation animation(&enemy_texture, m_imageCount, switchTime);
	animation1 = animation;
	this->speed = speed;
	row = 0;

	isAlive = true;
}

void AIEnemy::Update(Map& map, float deltaTime, sf::RenderWindow& window)
{
	setPosition(map);
	drawEnemy(window);
	movement(deltaTime, map);
}

void AIEnemy::setPosition(Map& map)
{
	if (ok == 0)
	{
		for (uint16_t index_x = 0;index_x < map.GetSize().x;index_x++)
		{
			for (uint16_t index_y = 0;index_y < map.GetSize().y;index_y++)
			{
				if (map.GetMapTiles()[index_x][index_y].GetType() == 0)
				{
					size.x = 80;
					size.y = 80;
					m_sprite.setPosition(map.GetMapTiles()[index_x][index_y].GetCoordinates().first + m_sprite.getSize().x + 25, map.GetMapTiles()[index_x][index_y].GetCoordinates().second + m_sprite.getSize().y + 25);
					m_sprite.setSize(size);
					ok = 1;
				}
			}
		}
	}
}

sf::Vector2u AIEnemy::getPositionOnMap(Map& map)
{
	float min = size.x * size.y;
	position.x = map.GetMapTiles()[0][0].GetSprite().getPosition().x + m_sprite.getSize().x / 2;
	position.y = map.GetMapTiles()[0][0].GetSprite().getPosition().y + m_sprite.getSize().y / 2;

	for (int indexX = 0; indexX < map.GetSize().x; indexX++)
	{
		for (int indexY = 0; indexY < map.GetSize().y; indexY++)
			{
				if (distance(getCenterPosition().x, getCenterPosition().y, map.GetMapTiles()[indexX][indexY].GetSprite().getPosition().x + m_sprite.getSize().x / 2, map.GetMapTiles()[indexX][indexY].GetSprite().getPosition().y + m_sprite.getSize().y / 2) < min)
				{
					min = distance(getCenterPosition().x, getCenterPosition().y, map.GetMapTiles()[indexX][indexY].GetSprite().getPosition().x + m_sprite.getSize().x / 2, map.GetMapTiles()[indexX][indexY].GetSprite().getPosition().y + m_sprite.getSize().y / 2);
					position.x = indexX;
					position.y = indexY;
				}
			}
		}

	return position;
}

void AIEnemy::movement(float deltaTime, Map& map)
{
	sf::Vector2f movement(0.0f, 0.0f);
	decisions(map);
	if (direction.compare("UP") == 0)
	{
		movement.y -= speed * deltaTime;
		animation1.axuCurrentImage.y = 9;
	}
	if (direction.compare("DOWN") == 0)
	{
		movement.y += speed * deltaTime;
		animation1.axuCurrentImage.y = 3;
	}
	
	if (direction.compare("RIGHT") == 0)
	{
		movement.x+= speed * deltaTime;
		animation1.axuCurrentImage.y = 0;
	}

	if (direction.compare("LEFT") == 0)
	{
		movement.x -= speed * deltaTime;
		animation1.axuCurrentImage.y = 6;
	}
	
	
	if (movement.x == 0 && movement.y == 0)
	{
		animation1.update(0, deltaTime, axuCurrentImage.y, 1);
	}
	else
	{
		animation1.update(0, deltaTime, axuCurrentImage.y, 3);
	}
	m_sprite.setTextureRect(animation1.uvRect);
	m_sprite.move(movement);
}

void AIEnemy::drawEnemy(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

bool AIEnemy::isGoingToCollide(Map& map)
{
	if (direction.compare("UP") == 0)
	{
		if (map.GetMapTiles()[getPositionOnMap(map).x][getPositionOnMap(map).y - 1].GetType() == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	if (direction.compare("DOWN") == 0)
	{
		if (map.GetMapTiles()[getPositionOnMap(map).x][getPositionOnMap(map).y + 1].GetType() == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	if (direction.compare("RIGHT") == 0)
	{
		if (map.GetMapTiles()[getPositionOnMap(map).x + 1][getPositionOnMap(map).y].GetType() == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	if (direction.compare("LEFT") == 0)
	{
		if (map.GetMapTiles()[getPositionOnMap(map).x - 1][getPositionOnMap(map).y].GetType() == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

bool AIEnemy::isOnEdge(Map& map)
{
	if (map.GetMapTiles()[getPositionOnMap(map).x][getPositionOnMap(map).y - 1].GetType() == 10
		|| map.GetMapTiles()[getPositionOnMap(map).x][getPositionOnMap(map).y + 1].GetType() == 10
		|| map.GetMapTiles()[getPositionOnMap(map).x - 1][getPositionOnMap(map).y].GetType() == 10
		|| map.GetMapTiles()[getPositionOnMap(map).x + 1][getPositionOnMap(map).y].GetType() == 10)
	{
		return true;
	}
	return false;
}


void AIEnemy::decisions(Map& map)
{
	int randAux;
	randAux=rand() % 4;
	randAux = std::clamp(randAux, 1, 4);
	if ((isGoingToCollide(map) || isOnEdge(map)) && direction.compare("UP") == 0)
	{
		direction = Directions[randAux];
	}
	else if ((isGoingToCollide(map) || isOnEdge(map)) && direction.compare("DOWN") == 0)
	{
		direction = Directions[randAux];
	}
	else if((isGoingToCollide(map) || isOnEdge(map)) && direction.compare("LEFT") == 0)
	{
		direction = Directions[randAux];
	}
	else if((isGoingToCollide(map) || isOnEdge(map)) && direction.compare("RIGHT") == 0)
	{
		srand(NULL);
		direction = Directions[randAux];
	}
	if (randAux == 4)
	{
		srand(NULL);
	}
}

sf::Vector2f AIEnemy::getCenterPosition()
{
	return sf::Vector2f(m_sprite.getPosition().x + size.x / 2, m_sprite.getPosition().y + size.y / 2);
}

float AIEnemy::distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

AIEnemy::AIEnemy()
{
}

