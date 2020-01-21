#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include "Player.h"
#include "Map.h"
#include "Explosion.h"
#include "Controller.h"

class Bomb {
private:
	sf::RectangleShape sprBomb;
	sf::Vector2f size;
	sf::Texture texture;
	sf::Clock clock;
	uint16_t bombNumber;
	std::vector<sf::Vector2u> position;

	std::vector<std::pair<sf::RectangleShape, float>> explosionVector;
	
	float deltaTimeBomb;

	uint16_t explosionSize;
	float explosionDeltaTime;
	uint16_t iterator;

	//animatie
	sf::IntRect animationRect;
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float switchTime;
	float animationDeltaTime;


public:
	std::vector <std::pair<sf::RectangleShape, float>> vecBomb;
	bool placedBomb;

	Bomb();
	~Bomb();
	Bomb(std::string bombTextureDirectory);

	void placeBomb(Map& map, Player& player, ControlHandler& handler);
	void drawBomb(sf::RenderWindow& window, float deltaTime);

	void explodeCenter(Map& map, Explosion& explosion, int i);
	void explodeUp(Map& map, Explosion& explosion, int i);
	void explodeDown(Map& map, Explosion& explosion, int i);
	void explodeLeft(Map& map, Explosion& explosion, int i);
	void explodeRight(Map& map, Explosion& explosion, int i);
	void createExplosion(Map& map, Explosion& explosion, int i);
	void deleteBomb(Map& map,Explosion& explosion, float deltaTime);
	void drawExplosion(sf::RenderWindow& window);
	void deleteExplosion(float deltaTime);

	sf::Vector2u getBombPositionOnMap(int i);

	//animation
	void update(float deltaTime);

	void functionality(float& deltaTime, Map& map, sf::RenderWindow& window,
		ControlHandler& handler, Explosion& explosion, Player& player);	
};

