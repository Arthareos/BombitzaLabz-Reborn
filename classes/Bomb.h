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
	sf::RectangleShape m_sprite;
	sf::Vector2f m_size;
	sf::Texture m_texture;
	sf::Clock m_clock;
	uint16_t m_bombNumber;
	std::vector<sf::Vector2u> m_position;

	std::vector<std::pair<sf::RectangleShape, float>> m_explosionsVector;
	
	float m_deltaTimeBomb;

	uint16_t m_explosionSize;

public:
	std::vector <std::pair<sf::RectangleShape, float>> vecBomb;
	bool placedBomb;

	Bomb();
	Bomb(std::string bombTextureDirectory);
	~Bomb();

	void PlaceBomb(Map& map, Player& player, Control& control);
	void DrawBomb(sf::RenderWindow& window, float deltaTime);

	void ExplodeCenter(Map& map, Player& player, Explosion& explosion, int i);
	void ExplodeUp(Map& map, Player& player, Explosion& explosion, int i);
	void ExplodeDown(Map& map, Player& player, Explosion& explosion, int i);
	void ExplodeLeft(Map& map, Player& player, Explosion& explosion, int i);
	void ExplodeRight(Map& map, Player& player, Explosion& explosion, int i);
	void CreateExplosion(Map& map, Player& player, Explosion& explosion, int i);
	void DeleteBomb(Map& map, Player& player, Explosion& explosion, float deltaTime);
	void DrawExplosion(sf::RenderWindow& window);
	void DeleteExplosion(float deltaTime);

	const sf::Vector2u& GetPositionOnMap(int i);

	void Functionality(float& deltaTime, Map& map, sf::RenderWindow& window,
		Control& control, Explosion& explosion, Player& player);	
};

