#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "PlayerAnimation.h"
#include "Map.h"
#include "Controller.h"

class Player : PlayerAnimation {
protected:
	sf::Texture m_texture;
	sf::Vector2f m_size;
	sf::Vector2f m_center;
	sf::Vector2u m_position;
	sf::RectangleShape m_sprite;
	sf::RectangleShape m_collisionDetector;
	sf::FloatRect m_nextPosition;

	float m_animationSwitchTime;
	float m_speed;

	PlayerAnimation m_animation;

	//Gameplay related proprerties
	uint16_t m_stage;
	uint16_t m_round;
	uint16_t m_lives;
	uint64_t m_score;
	uint64_t m_highscore;

public:	
	Player();
	Player(sf::Vector2u imageCount, uint16_t highscore);
	~Player();

	void SetPosition(Map& map, uint16_t position);
	void SetStage(uint16_t stage);
	void SetRound(uint16_t round);
	void SetLives(uint16_t lives);
	void SetScore(uint64_t score);
	void SetHighscore(uint64_t highscore);

	const sf::RectangleShape& GetSprite();
	const sf::Vector2f& GetCenterPosition();
	const sf::Vector2u& GetPositionOnMap(Map& map);
	const float& GetDistance(float x1, float y1, float x2, float y2);
	const sf::Vector2f& getSize();
	const uint16_t& GetStage();
	const uint16_t& GetRound();
	const uint16_t& GetLives();
	const uint64_t& GetScore();
	const uint64_t& GetHighscore();

	void Movement(float& deltaTime, Control& control, Map& map);
	bool MoveUp(float& deltaTime, Control& control, sf::Vector2f& movement);
	bool MoveDown(float& deltaTime, Control& control, sf::Vector2f& movement);
	bool MoveRight(float& deltaTime, Control& control, sf::Vector2f& movement);
	bool MoveLeft(float& deltaTime, Control& control, sf::Vector2f& movement);

	void DrawPlayer(sf::RenderWindow& window);
	void Functionality(float& deltaTime, Map& map, sf::RenderWindow& window, Control& control);
};

