#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Map.h"
#include "EnemyAnimation.h"

class AIEnemy : public EnemyAnimation {
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

public:
	AIEnemy();
	AIEnemy(sf::Vector2u imageCount);
	~AIEnemy();

	void SetPosition(Map& map);
	void SetDead(bool value);

	const sf::RectangleShape& GetSprite();
	const sf::Vector2f& GetCenterPosition();
	const sf::Vector2u& GetPositionOnMap(Map& map);
	const float& GetDistance(float x, float y);
	const sf::Vector2f& getSize();
	const bool& IsDead();

	void Draw(sf::RenderWindow& window);
	void Functionality(float& deltaTime, Map& map, sf::RenderWindow& window);
};

