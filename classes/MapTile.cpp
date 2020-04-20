#include "MapTile.h"

MapTile::MapTile()
{
	this->m_size = 1;
	this->m_type = 0;
	this->m_hasBomb = false;
	this->m_hasCrate = false;
	this->m_hasPowerUP = false;
	this->m_hasExit = false;
}

void MapTile::SetCoordinates(float_t x, float_t y)
{
	m_coordinates.first = x;
	m_coordinates.second = y;
}

void MapTile::SetIndex(uint16_t x, uint16_t y)
{
	this->m_index = std::make_pair(x, y);
}

void MapTile::SetTexture(std::string textureDirectory)
{
	if (!m_texture.loadFromFile(textureDirectory))
	{
		std::cout << " +> [ERROR] Tile texture NOT loaded;" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(m_size, m_size);
}

void MapTile::SetType(int16_t type)
{
	this->m_type = type;
	this->m_sprite.setPosition(type / 10, type % 10);
}