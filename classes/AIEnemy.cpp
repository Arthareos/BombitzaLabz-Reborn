#include "AIEnemy.h"

AIEnemy::AIEnemy() {}

AIEnemy::AIEnemy(sf::Vector2u imageCount)
{
	std::string textureDirectory = ".\\resources\\enemy.png";
	if (!m_texture.loadFromFile(textureDirectory))
	{
		std::cout << " +> [ERROR] Enemy texture NOT loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Enemy texture loaded;" << std::endl;

		m_sprite.setTexture(&m_texture);
	}

	m_animationSwitchTime = 0.1f;
	EnemyAnimation animation(&m_texture, imageCount, m_animationSwitchTime);
	m_animation = animation;
	m_size = sf::Vector2f(60, 60);
	m_sprite.setSize(m_size);
	m_collisionDetector.setSize(sf::Vector2f(40, 40));
	m_collisionDetector.setFillColor(sf::Color::Transparent);
	this->m_speed = 100.f;

	m_isDead = false;
}

AIEnemy::~AIEnemy() {}

void AIEnemy::Functionality(float& deltaTime, Map& map, sf::RenderWindow& window)
{
	Draw(window);
	Movement(deltaTime, map);
}

void AIEnemy::SetPosition(sf::Vector2f position, Map& map)
{
	m_sprite.setPosition(map.GetMapTiles().at(position.x).at(position.y).GetSprite().getPosition());
	m_collisionDetector.setPosition(m_sprite.getGlobalBounds().left + 12.f, m_sprite.getGlobalBounds().top + 20.0f);
}

void AIEnemy::SetDead(bool value)
{
	m_isDead = value;
}

const sf::Vector2u& AIEnemy::GetPositionOnMap(Map& map)
{
	float min = m_size.x * m_size.y;
	m_position.x = map.GetMapTiles()[0][0].GetSprite().getPosition().x + m_sprite.getSize().x / 2;
	m_position.y = map.GetMapTiles()[0][0].GetSprite().getPosition().y + m_sprite.getSize().y / 2;

	for (int indexX = 0; indexX < map.GetSize().x; indexX++)
	{
		for (int indexY = 0; indexY < map.GetSize().y; indexY++)
		{
			if (GetDistance(map.GetMapTiles()[indexX][indexY].GetSprite().getPosition().x + m_sprite.getSize().x / 2, map.GetMapTiles()[indexX][indexY].GetSprite().getPosition().y + m_sprite.getSize().y / 2) < min)
			{
				min = GetDistance(map.GetMapTiles()[indexX][indexY].GetSprite().getPosition().x + m_sprite.getSize().x / 2, map.GetMapTiles()[indexX][indexY].GetSprite().getPosition().y + m_sprite.getSize().y / 2);
				m_position.x = indexX;
				m_position.y = indexY;
			}
		}
	}

	return m_position;
}

void AIEnemy::Movement(float& deltaTime, Map& map)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (m_direction == 1)
	{
		movement.y -= m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 9;
	}
	else if (m_direction == 2)
	{
		movement.y += m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 3;

	}
	else if (m_direction == 3)
	{
		movement.x -= m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 6;
	}
	else if (m_direction == 4)
	{
		movement.x += m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 0;
	}

	m_moveCounter++;
	if (m_moveCounter >= m_movementLength)
	{
		m_direction = generateRandom(4);
		m_moveCounter = 0;
	}

	for (int indexX = 0; indexX < map.GetMapTiles().size(); indexX++)
	{
		for (int indexY = 0; indexY < map.GetMapTiles().at(indexX).size(); indexY++)
		{
			if (map.GetMapTiles().at(indexX).at(indexY).GetType() != 0)
			{
				sf::FloatRect enemyBounds = m_collisionDetector.getGlobalBounds();
				sf::FloatRect obstacleBounds = map.GetMapTiles().at(indexX).at(indexY).GetSprite().getGlobalBounds();

				m_nextPosition = enemyBounds;
				m_nextPosition.left += movement.x;
				m_nextPosition.top += movement.y;

				if (obstacleBounds.intersects(m_nextPosition))
				{
					//Bottom collision
					if (enemyBounds.top < obstacleBounds.top
						&& enemyBounds.top + enemyBounds.height < obstacleBounds.top + obstacleBounds.height
						&& enemyBounds.left < obstacleBounds.left + obstacleBounds.width
						&& enemyBounds.left + enemyBounds.width > obstacleBounds.left)
					{
						movement.y = 0.f;
					}
					else
						//Top collision
						if (enemyBounds.top > obstacleBounds.top
							&& enemyBounds.top + enemyBounds.height > obstacleBounds.top + obstacleBounds.height
							&& enemyBounds.left < obstacleBounds.left + obstacleBounds.width
							&& enemyBounds.left + enemyBounds.width > obstacleBounds.left)
						{
							movement.y = 0.f;
						}
						else
							//Right collision
							if (enemyBounds.left - 20 < obstacleBounds.left
								&& enemyBounds.left + enemyBounds.width < obstacleBounds.left + obstacleBounds.width
								&& enemyBounds.top < obstacleBounds.top + obstacleBounds.height
								&& enemyBounds.top + enemyBounds.height > obstacleBounds.top)
							{
								movement.x = 0.f;
							}
							else
								//Left collision
								if (enemyBounds.left + 20 > obstacleBounds.left
									&& enemyBounds.left + enemyBounds.width > obstacleBounds.left + obstacleBounds.width
									&& enemyBounds.top < obstacleBounds.top + obstacleBounds.height
									&& enemyBounds.top + enemyBounds.height > obstacleBounds.top)
								{
									movement.x = 0.f;
								}
				}
			}
		}
	}

	if (movement.x == 0 && movement.y == 0)
	{
		m_animation.Update(0, deltaTime, m_auxCurrentImage.y, 1);
	}
	else
	{
		m_animation.Update(0, deltaTime, m_auxCurrentImage.y, 3);
	}

	m_sprite.setTextureRect(m_animation.m_uvRect);
	m_sprite.move(movement);
	m_collisionDetector.move(movement);
}

void AIEnemy::Draw(sf::RenderWindow& window)
{
	m_sprite.setTexture(&m_texture);
	window.draw(m_sprite);
}

sf::RectangleShape& AIEnemy::GetSprite()
{
	return m_sprite;
}

const sf::Vector2f& AIEnemy::GetCenterPosition()
{
	return sf::Vector2f(m_sprite.getPosition().x + m_size.x / 2, m_sprite.getPosition().y + m_size.y / 2);
}

const float& AIEnemy::GetDistance(float x, float y)
{
	return sqrt(pow((x - GetCenterPosition().x), 2) + pow((y - GetCenterPosition().y), 2));
}

const sf::Vector2f& AIEnemy::getSize()
{
	return m_size;
}

const bool& AIEnemy::IsDead()
{
	return m_isDead;
}
