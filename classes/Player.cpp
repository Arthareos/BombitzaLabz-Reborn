#include "Player.h"

Player::Player() {}

//0 for top-left, 1 for bottom-right, 2 for top-right, 3 for bottom-left
Player::Player(sf::Vector2u imageCount, uint16_t highscore)
{
	if (!m_texture.loadFromFile(".\\resources\\bomberman.png"))
	{
		std::cout << " +> [ERROR] Player texture NOT loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Player texture loaded;" << std::endl;
		m_sprite.setTexture(&m_texture);
	}

	m_animationSwitchTime = 0.1f;
	PlayerAnimation animation(&m_texture, imageCount, m_animationSwitchTime);
	m_animation = animation;
	m_size = sf::Vector2f(60, 60);
	m_sprite.setSize(m_size);
	m_collisionDetector.setSize(sf::Vector2f(40, 40));
	m_collisionDetector.setFillColor(sf::Color::Transparent);

	this->m_speed = 100.0f;

	//Gameplay setup
	m_stage = 1;
	m_round = 1;
	m_lives = 2;
	m_score = 0;
	m_highscore = highscore;
	m_isDead = false;
}

Player::~Player() {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Player::SetPosition(Map& map, uint16_t position)
{
	sf::Vector2f aux;

	switch (position) {
	case 0:
		aux = sf::Vector2f(map.GetMapTiles().at(1).at(1).GetSprite().getPosition().x, map.GetMapTiles().at(1).at(1).GetSprite().getPosition().y);
		break;
	case 1:
		aux = sf::Vector2f(map.GetMapTiles().at(map.GetSize().x - 2).at(map.GetSize().y - 2).GetSprite().getPosition().x, map.GetMapTiles().at(map.GetSize().x - 2).at(map.GetSize().y - 2).GetSprite().getPosition().y);
		break;
	case 2:
		aux = sf::Vector2f(map.GetMapTiles().at(map.GetSize().x - 2).at(1).GetSprite().getPosition().x, map.GetMapTiles().at(map.GetSize().x - 2).at(1).GetSprite().getPosition().y);
		break;
	case 3:
		aux = sf::Vector2f(map.GetMapTiles().at(1).at(map.GetSize().y - 2).GetSprite().getPosition().x, map.GetMapTiles().at(1).at(map.GetSize().y - 2).GetSprite().getPosition().y);
		break;
	default:
		aux = sf::Vector2f(map.GetMapTiles().at(1).at(1).GetSprite().getPosition().x, map.GetMapTiles().at(1).at(1).GetSprite().getPosition().y);
		break;
	}

	m_sprite.setPosition(aux.x, aux.y);
	m_collisionDetector.setPosition(m_sprite.getGlobalBounds().left + 12.f,	m_sprite.getGlobalBounds().top + 20.0f);
}

void Player::SetStage(uint16_t stage)
{
	this->m_stage = stage;
}

void Player::SetRound(uint16_t round)
{
	this->m_round = round;
}

void Player::SetLives(uint16_t lives)
{
	this->m_lives = lives;
}

void Player::SetScore(uint64_t score)
{
	this->m_score = score;
}

void Player::SetHighscore()
{
	if (m_score > m_highscore)
	{
		m_highscore = m_score;
	}
}

void Player::SetDead(bool value)
{
	this->m_isDead = value;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const sf::RectangleShape& Player::GetSprite()
{
	return this->m_sprite;
}

const sf::Vector2f& Player::GetCenterPosition()
{
	return sf::Vector2f(m_sprite.getPosition().x + m_size.x / 2, m_sprite.getPosition().y + m_size.y / 2);
}

const sf::Vector2u& Player::GetPositionOnMap(Map& map)
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

const float& Player::GetDistance(float x, float y)
{
	return sqrt(pow(x - GetCenterPosition().x, 2) + pow((y - GetCenterPosition().y), 2));
}

const sf::Vector2f& Player::getSize()
{
	return this->m_size;
}

const uint16_t& Player::GetStage()
{
	return m_stage;
}

const uint16_t& Player::GetRound()
{
	return m_round;
}

const uint16_t& Player::GetLives()
{
	return m_lives;
}

const uint64_t& Player::GetScore()
{
	return m_score;
}

const uint64_t& Player::GetHighscore()
{
	return m_highscore;
}

const bool& Player::IsDead()
{
	return m_isDead;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Player::Movement(float& deltaTime, Control& control, Map& map)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (!MoveUp(deltaTime, control, movement))
	{
		if (!MoveDown(deltaTime, control, movement))
		{
			if (!MoveRight(deltaTime, control, movement))
			{
				if (!MoveLeft(deltaTime, control, movement))
				{

				}
			}
		}
	}

	//Collision Detection
	for (int indexX = 0; indexX < map.GetMapTiles().size(); indexX++)
	{
		for (int indexY = 0; indexY < map.GetMapTiles().at(indexX).size(); indexY++)
		{
			if (map.GetMapTiles().at(indexX).at(indexY).GetType() != 0)
			{
				sf::FloatRect playerBounds = m_collisionDetector.getGlobalBounds();

				sf::FloatRect obstacleBounds = map.GetMapTiles().at(indexX).at(indexY).GetSprite().getGlobalBounds();

				m_nextPosition = playerBounds;
				m_nextPosition.left += movement.x;
				m_nextPosition.top += movement.y;

				if (obstacleBounds.intersects(m_nextPosition))
				{
					//Bottom collision
					if (playerBounds.top < obstacleBounds.top
						&& playerBounds.top + playerBounds.height < obstacleBounds.top + obstacleBounds.height
						&& playerBounds.left < obstacleBounds.left + obstacleBounds.width
						&& playerBounds.left + playerBounds.width > obstacleBounds.left)
					{
						movement.y = 0.f;
					}
					else
						//Top collision
						if (playerBounds.top > obstacleBounds.top
							&& playerBounds.top + playerBounds.height > obstacleBounds.top + obstacleBounds.height
							&& playerBounds.left < obstacleBounds.left + obstacleBounds.width
							&& playerBounds.left + playerBounds.width > obstacleBounds.left)
						{
							movement.y = 0.f;
						}
						else
							//Right collision
							if (playerBounds.left - 20 < obstacleBounds.left
								&& playerBounds.left + playerBounds.width < obstacleBounds.left + obstacleBounds.width
								&& playerBounds.top < obstacleBounds.top + obstacleBounds.height
								&& playerBounds.top + playerBounds.height > obstacleBounds.top)
							{
								movement.x = 0.f;
							}
							else
								//Left collision
								if (playerBounds.left + 20 > obstacleBounds.left
									&& playerBounds.left + playerBounds.width > obstacleBounds.left + obstacleBounds.width
									&& playerBounds.top < obstacleBounds.top + obstacleBounds.height
									&& playerBounds.top + playerBounds.height > obstacleBounds.top)
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

bool Player::MoveUp(float& deltaTime, Control& control, sf::Vector2f& movement)
{
	if ((((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && control.GoUp())
	{
		movement.y -= m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 9;
		return true;
	}
	return false;
}

bool Player::MoveDown(float& deltaTime, Control& control, sf::Vector2f& movement)
{
	if ((((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && control.GoDown())
	{
		movement.y += m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 0;
		return true;
	}
	return false;
}

bool Player::MoveRight(float& deltaTime, Control& control, sf::Vector2f& movement)
{
	if ((((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX)) > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && control.GoRight())
	{
		movement.x += m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 3;
		return true;
	}
	return false;
}

bool Player::MoveLeft(float& deltaTime, Control& control, sf::Vector2f& movement)
{
	if ((((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX)) < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && control.GoLeft())
	{
		movement.x -= m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 6;
		return true;
	}
	return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_collisionDetector);
	window.draw(m_sprite);
}

void Player::Functionality(float& deltaTime, Map& map, sf::RenderWindow& window, Control& control)
{
	Movement(deltaTime, control, map);
	Draw(window);
}