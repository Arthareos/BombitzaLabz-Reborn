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

void MapTile::SetSize(float_t size)
{
	this->m_size = size;
}

void MapTile::SetType(int16_t type)
{
	this->m_type = type;
	this->m_sprite.setPosition(type / 10, type % 10);
}

void MapTile::SetBomb(bool value)
{
	this->m_hasBomb = value;
}

void MapTile::SetCrate(bool value)
{
	this->m_hasCrate = value;
}

std::pair<float_t, float_t>& MapTile::GetCoordinates()
{
	return this->m_coordinates;
}

std::pair<uint16_t, uint16_t>& MapTile::GetIndex()
{
	return m_index;
}

sf::Sprite* MapTile::GetSprite()
{
	return &this->m_sprite;
}

float_t MapTile::GetSize()
{
	return this->m_size;
}

int16_t MapTile::GetType()
{
	return this->m_type;
}

bool MapTile::GetBomb()
{
	return this->m_hasBomb;
}

bool MapTile::GetCrate()
{
	return this->m_hasCrate;
}

void MapTile::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}