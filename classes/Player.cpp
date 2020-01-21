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
	m_size = sf::Vector2f(70, 70);
	m_sprite.setSize(m_size);

	this->m_speed = 100.0f;

	//Gameplay setup
	m_stage = 1;
	m_round = 1;
	m_lives = 2;
	m_score = 0;
	m_highscore = highscore;
}

Player::~Player() {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Player::SetPosition(Map& map, uint16_t position)
{
	sf::Vector2f aux;
	switch (position) {
	case 0:
		aux = sf::Vector2f(map.GetMapTiles().at(1).at(1).GetSprite()->getPosition().x, map.GetMapTiles().at(1).at(1).GetSprite()->getPosition().y);
		break;
	case 1:
		aux = sf::Vector2f(map.GetMapTiles().at(map.GetSize().x - 2).at(map.GetSize().y - 2).GetSprite()->getPosition().x, map.GetMapTiles().at(map.GetSize().x - 2).at(map.GetSize().y - 2).GetSprite()->getPosition().y);
		break;
	case 2:
		aux = sf::Vector2f(map.GetMapTiles().at(map.GetSize().x - 2).at(1).GetSprite()->getPosition().x, map.GetMapTiles().at(map.GetSize().x - 2).at(1).GetSprite()->getPosition().y);
		break;
	case 3:
		aux = sf::Vector2f(map.GetMapTiles().at(1).at(map.GetSize().y - 2).GetSprite()->getPosition().x, map.GetMapTiles().at(1).at(map.GetSize().y - 2).GetSprite()->getPosition().y);
		break;
	default:
		aux = sf::Vector2f(map.GetMapTiles().at(1).at(1).GetSprite()->getPosition().x, map.GetMapTiles().at(1).at(1).GetSprite()->getPosition().y);
		break;
	}

	m_sprite.setPosition(aux.x, aux.y);
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

void Player::SetHighscore(uint64_t highscore)
{
	this->m_highscore = highscore;
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
	m_position.x = map.GetMapTiles()[0][0].GetSprite()->getPosition().x + m_sprite.getSize().x / 2;
	m_position.y = map.GetMapTiles()[0][0].GetSprite()->getPosition().y + m_sprite.getSize().y / 2;

	for (int indexX = 0; indexX < map.GetSize().x; indexX++)
	{
		for (int indexY = 0; indexY < map.GetSize().y; indexY++)
		{
			if (GetDistance(GetCenterPosition().x, GetCenterPosition().y, map.GetMapTiles()[indexX][indexY].GetSprite()->getPosition().x + m_sprite.getSize().x / 2, map.GetMapTiles()[indexX][indexY].GetSprite()->getPosition().y + m_sprite.getSize().y / 2) < min)
			{
				min = GetDistance(GetCenterPosition().x, GetCenterPosition().y, map.GetMapTiles()[indexX][indexY].GetSprite()->getPosition().x + m_sprite.getSize().x / 2, map.GetMapTiles()[indexX][indexY].GetSprite()->getPosition().y + m_sprite.getSize().y / 2);
				m_position.x = indexX;
				m_position.y = indexY;
			}
		}
	}

	return m_position;
}

const float& Player::GetDistance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Player::Movement(float& deltaTime, ControlHandler& handler)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (!MoveUp(deltaTime, handler, movement))
	{
		if (!MoveDown(deltaTime, handler, movement))
		{
			if (!MoveRight(deltaTime, handler, movement))
			{
				if (!MoveLeft(deltaTime, handler, movement))
				{

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
}

bool Player::MoveUp(float& deltaTime, ControlHandler& handler, sf::Vector2f& movement)
{
	if ((((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && handler.GoUp(0))
	{
		movement.y -= m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 9;
		return true;
	}
	return false;
}

bool Player::MoveDown(float& deltaTime, ControlHandler& handler, sf::Vector2f& movement)
{
	if ((((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && handler.GoDown(0))
	{
		movement.y += m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 0;
		return true;
	}
	return false;
}

bool Player::MoveRight(float& deltaTime, ControlHandler& handler, sf::Vector2f& movement)
{
	if ((((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX)) > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && handler.GoRight(0))
	{
		movement.x += m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 3;
		return true;
	}
	return false;
}

bool Player::MoveLeft(float& deltaTime, ControlHandler& handler, sf::Vector2f& movement)
{
	if ((((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX)) < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && handler.GoLeft(0))
	{
		movement.x -= m_speed * deltaTime;
		m_animation.m_auxCurrentImage.y = 6;
		return true;
	}
	return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Player::DrawPlayer(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Player::Functionality(float& deltaTime, Map& map, sf::RenderWindow& window, ControlHandler& handler)
{
	Movement(deltaTime, handler);
	DrawPlayer(window);
}