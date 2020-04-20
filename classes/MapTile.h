#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

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
	void SetSize(float_t size) { this->m_size = size; };
	void SetType(int16_t type);
	void SetBomb(bool value) { this->m_hasBomb = value; };
	void SetCrate(bool value) { this->m_hasCrate = value; };

	std::pair<float_t, float_t>& GetCoordinates() { return this->m_coordinates; };
	std::pair<uint16_t, uint16_t>& GetIndex() { return m_index; };
	sf::Sprite& GetSprite() { return this->m_sprite; };
	const float_t& GetSize() { return this->m_size; };
	const int16_t& GetType() { return this->m_type; };
	const bool& HasBomb() { return this->m_hasBomb; };
	const bool& HasCrate() { return this->m_hasCrate; };

	void Draw(sf::RenderWindow& window) { window.draw(m_sprite); };
};
