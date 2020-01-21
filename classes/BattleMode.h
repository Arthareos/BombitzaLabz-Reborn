#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Controller.h"
#include "BattleStart.h"
#include "Resources.h"

void BattleMode(int16_t& gameState, sf::RenderWindow& window, ControlHandler& handler);