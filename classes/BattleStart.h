#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Controller.h"
#include "BattlePlayer.h"
#include "BattleScoreboard.h"
#include "Map.h"

enum class Type {
	local,
	lan,
	internet
};

class Config {
private:
	uint16_t m_nrPlayers;
	Type m_networkType;
	uint16_t m_nrRounds;

public:
	Config();
	~Config();

	void SetPlayers(uint16_t number);
	void SetNetworkType(Type type);
	void SetNumberRounds(uint16_t nrRounds);

	const uint16_t& GetNumberOfPlayers();
	const Type& GetNetworkType();
	const uint16_t& GetNumberRounds();
};

class BattleStart {
private:
	Map m_map;
	BattleScoreboard m_scoreboard;

public:
	BattleStart(sf::RenderWindow& window, ControlHandler& handler, int16_t& gameState,
		std::vector<BattlePlayer>& players);

	const bool& isOver(std::vector<BattlePlayer>& players);
};

