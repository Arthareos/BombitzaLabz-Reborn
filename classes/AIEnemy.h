#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Map.h"
#include "EnemyAnimation.h"
#include "Random.h"

class AIEnemy : public EnemyAnimation, Random {
protected:
	sf::Texture m_texture;
	sf::Vector2f m_size;
	sf::Vector2f m_center;
	sf::Vector2u m_position;
	sf::RectangleShape m_sprite;
	sf::RectangleShape m_collisionDetector;
	sf::FloatRect m_nextPosition;

	EnemyAnimation m_animation;

	float m_animationSwitchTime;
	float m_speed;
	bool m_isDead;

	int m_direction = 0; //1->UP 2->DOWN 3->LEFT 4->RIGHT
	int m_movementLength = 50;
	int m_moveCounter = 0;

public:
	AIEnemy();
	AIEnemy(sf::Vector2u imageCount);
	~AIEnemy();

	void SetPosition(sf::Vector2f position, Map& map);
	void SetDead(bool value);

	sf::RectangleShape& GetSprite();
	const sf::Vector2f& GetCenterPosition();
	const sf::Vector2u& GetPositionOnMap(Map& map);
	const float& GetDistance(float x, float y);
	const sf::Vector2f& getSize();
	const bool& IsDead();

	void Movement(float& deltaTime, Map& map);
	void Draw(sf::RenderWindow& window);
	void Functionality(float& deltaTime, Map& map, sf::RenderWindow& window);
};

