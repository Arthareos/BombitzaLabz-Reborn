#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Crate.h"

class MapTile {
private:
	std::pair<float_t, float_t> m_coordinates;
	std::pair<uint16_t, uint16_t> m_index;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	float_t m_size;
	int16_t m_type;
	bool m_hasBomb;
	bool m_hasCrate;
	bool m_hasPowerUP;
	bool m_hasExit;

public:	
	MapTile();

	void SetCoordinates(float_t x, float_t y);
	void SetIndex(uint16_t x, uint16_t y);
	void SetTexture(std::string textureDirectory);
	void SetSize(float_t size);
	void SetType(int16_t type);
	void SetBomb(bool value);
	void SetCrate(bool value);

	std::pair<float_t, float_t>& GetCoordinates();
	std::pair<uint16_t, uint16_t>& GetIndex();
	sf::Sprite& GetSprite();
	const float_t& GetSize();
	const int16_t& GetType();
	const bool& HasBomb();
	const bool& HasCrate();

	void Draw(sf::RenderWindow& window);
};
