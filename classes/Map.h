#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <utility>
#include <cstdint>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "MapTile.h"

enum class Biome {
	glacial,
	tundra,
	sand,
	castle
};

class Map {
private:
	std::vector<std::vector<MapTile>> m_tiles;
	int16_t m_width;
	int16_t m_height;

	int16_t m_offsetWidth;
	int16_t m_offsetHeight;

public:
	Map();
	Map(sf::RenderWindow& window, int16_t width, int16_t height, Biome biome);
	
	const bool PositionValidator(int width, int height);
	std::vector<std::vector<MapTile>>& GetMapTiles();
	sf::Vector2f GetSize();

	uint16_t GetCrates();
	void DestroyCrate(uint16_t indexX, uint16_t indexY);
	void DrawMap(sf::RenderWindow& window);
};