#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Resources.h"
#include "Map.h"
#include "BattlePlayer.h"
#include "Scoreboard.h"

class BattleScoreboard : public Scoreboard {
private:

public:
	BattleScoreboard();
	BattleScoreboard(Map& map, std::vector<BattlePlayer>& players);

	void Draw(sf::RenderWindow& window, std::vector<BattlePlayer>& players);
};

