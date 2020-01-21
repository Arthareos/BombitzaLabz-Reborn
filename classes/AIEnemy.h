#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Map.h"
#include "EnemyAnimation.h"

class AIEnemy : public EnemyAnimation {
public:

	sf::Texture enemy_texture;
	float speed;
	unsigned int row;
	int ok = 0;
	sf::Vector2f size;
	sf::Vector2f center;
	sf::Vector2u position;
	sf::Vector2u position2;

	sf::RectangleShape m_sprite;
	float auxDeltaTime = 0.0f;
	EnemyAnimation animation1;

	std::vector<std::string> Directions{ "","UP","DOWN","LEFT","RIGHT" };

	std::string direction = "RIGHT";
	bool isAlive;



	AIEnemy();
	AIEnemy(std::string imageDirectory, sf::Vector2u imageCount, float switchTime, float speed);
	void Update(Map& map, float deltaTime, sf::RenderWindow& window);

	void setPosition(Map& map);
	sf::Vector2u getPositionOnMap(Map& map);
	std::vector<std::vector<MapTile>>& getMapTiles();
	void movement(float deltaTime, Map& map);
	void drawEnemy(sf::RenderWindow& window);
	bool isGoingToCollide(Map& map);
	bool isOnEdge(Map& map);
	void decisions(Map& map);
	float distance(float x1, float y1, float x2, float y2);

	sf::Vector2f getCenterPosition();

	
};

