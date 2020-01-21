#include "AIEnemy.h"

AIEnemy::AIEnemy() {}

AIEnemy::AIEnemy(sf::Vector2u imageCount)
{
	if (!m_texture.loadFromFile(".\\resources\\enemy.png"))
	{
		std::cout << " +> [ERROR] Enemy texture NOT loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Enemy texture loaded;" << std::endl;
		m_sprite.setTexture(&m_texture);
	}

	EnemyAnimation animation(&m_texture, m_imageCount, switchTime);
	m_animation = animation;
	m_size = sf::Vector2f(60, 60);
	m_sprite.setSize(m_size);
	m_collisionDetector.setSize(sf::Vector2f(40, 40));
	m_collisionDetector.setFillColor(sf::Color::Transparent);

	this->m_speed = 100.0f;
	m_isDead = false;
}

AIEnemy::~AIEnemy() {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void AIEnemy::SetPosition(Map& map)
{

}

void AIEnemy::SetDead(bool value)
{
	this->m_isDead = value;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const sf::RectangleShape& AIEnemy::GetSprite()
{
	return m_sprite;
}

const sf::Vector2f& AIEnemy::GetCenterPosition()
{
	return sf::Vector2f(m_sprite.getPosition().x + m_size.x / 2, m_sprite.getPosition().y + m_size.y / 2);
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

const float& AIEnemy::GetDistance(float x, float y)
{
	return sqrt(pow(x - GetCenterPosition().x, 2) + pow((y - GetCenterPosition().y), 2));
}

const sf::Vector2f& AIEnemy::getSize()
{
	return m_size;
}

const bool& AIEnemy::IsDead()
{
	return m_isDead;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void AIEnemy::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void AIEnemy::Functionality(float& deltaTime, Map& map, sf::RenderWindow& window)
{
	Draw(window);
}
