#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Resources.h"
#include "Map.h"
#include "Player.h"

class Scoreboard {
protected:
	sf::RectangleShape m_wrapper;
	Text m_text;

	uint16_t m_lives;
	uint64_t m_score;
	uint64_t m_highscore;
	sf::Clock m_clock;
	float m_roundLenght;

public:
	Scoreboard();
	Scoreboard(Map& map, Player& player, int time);

	void AddScore(uint64_t& score);
	void SetHighscore();
	void SetTimer(int16_t& seconds);
	void SetLives(uint16_t& lives);

	const uint64_t& GetScore();
	const uint64_t& GetHighscore();
	const int16_t& GetElapsedTime();
	const int16_t& GetRemainingTime();
	const uint16_t& GetLives();

	void draw(sf::RenderWindow& window, float deltaTime);
};

