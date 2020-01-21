#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>

#include "Resources.h"
#include "Map.h"
#include "Player.h"
#include "AIEnemy.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Scoreboard.h"
#include "Controller.h"

class GameRound {
private:
	Map m_map;
	Bomb m_bomb;
	Explosion m_explosion;
	std::vector<AIEnemy> m_enemies;
	Scoreboard m_scoreboard;
public:
	GameRound(sf::RenderWindow& window, ControlHandler& handler, int16_t& gameState, Player& player);

	Map& GetMap();
	std::vector<AIEnemy>& GetEnemies();
};