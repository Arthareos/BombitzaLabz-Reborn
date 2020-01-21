#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <chrono>
#include <string>

#include "GameRound.h"
#include "Resources.h"
#include "Controller.h"

void gameStart(int16_t& gameState, sf::RenderWindow& window, ControlHandler& handler, uint64_t highscore);