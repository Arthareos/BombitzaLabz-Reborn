#include "Map.h"

Map::Map() {}

//height and width in tile number
Map::Map(sf::RenderWindow& window, int16_t width, int16_t height, Biome biome)
{
	m_offsetWidth = window.getSize().x / 2 - width * 32;
	m_offsetHeight = window.getSize().y / 2 - height * 32 + 32;

	this->m_width = width;
	this->m_height = height;

	std::string textureDirectory;
	srand(time(NULL));

	switch (biome)	{
	case Biome::glacial:
		textureDirectory = ".\\\\resources\\\\glacial.png";
		break;
	case Biome::tundra:
		textureDirectory = ".\\\\resources\\\\tundra.png";
		break;
	case Biome::sand:
		textureDirectory = ".\\\\resources\\\\sand.png";
		break;
	case Biome::castle:
		textureDirectory = ".\\\\resources\\\\castle.png";
		break;
	}

	std::vector<std::vector<int16_t>> matrix;
	matrix.resize(width);
	m_tiles.resize(width);
	for (uint16_t indexX = 0; indexX < width; indexX++)
	{
		matrix.at(indexX).resize(height);
		m_tiles.at(indexX).resize(height);
		for (uint16_t indexY = 0; indexY < height; indexY++)
		{
			if (indexX % 2 == 0 && indexY % 2 == 0)
			{
				matrix.at(indexX).at(indexY) = 11;
			}
			else
			{
				matrix.at(indexX).at(indexY) = 0;
			}
		}
	}

	for (uint16_t index = 0; index < width; index++)
	{
		matrix.at(index).at(0) = 10;
		matrix.at(index).at(height - 1) = 10;
	}

	for (uint16_t index = 0; index < height; index++)
	{
		matrix.at(0).at(index) = 10;
		matrix.at(width - 1).at(index) = 10;
	}

	for (uint16_t indexX = 0; indexX < width; indexX++)
	{
		for (uint16_t indexY = 0; indexY < height; indexY++)
		{
			m_tiles.at(indexX).at(indexY).SetCoordinates(indexX, indexY);
			m_tiles.at(indexX).at(indexY).SetType(matrix[indexX][indexY]);
			m_tiles.at(indexX).at(indexY).SetTexture(textureDirectory);
			m_tiles.at(indexX).at(indexY).SetCrate(false);
			m_tiles.at(indexX).at(indexY).SetIndex(indexX, indexY);

			m_tiles.at(indexX).at(indexY).GetSprite().setScale(2, 2);
			m_tiles.at(indexX).at(indexY).GetSprite().setTextureRect(sf::IntRect(m_tiles.at(indexX).at(indexY).GetSprite().getPosition().x * 32, m_tiles.at(indexX).at(indexY).GetSprite().getPosition().y * 32, 32, 32));
			m_tiles.at(indexX).at(indexY).SetCoordinates(indexX + m_offsetWidth, indexY + m_offsetHeight);
			m_tiles.at(indexX).at(indexY).GetSprite().setPosition(indexX * 64 + m_offsetHeight, indexY * 64 + m_offsetWidth);
		}
	}

	int16_t numberCrates = 32;
	int auxHeight, auxWidth;
	while (numberCrates)
	{
		auxHeight = rand() % height;
		auxWidth = rand() % width;

		auxHeight = std::clamp(auxHeight, 1, (int)height - 1);
		auxWidth = std::clamp(auxWidth, 1, (int)width - 1);

		if (PositionValidator(auxWidth, auxHeight))
		{
			m_tiles.at(auxWidth).at(auxHeight).SetCrate(true);
			m_tiles.at(auxWidth).at(auxHeight).SetType(1);
			m_tiles.at(auxWidth).at(auxHeight).SetTexture(textureDirectory);
			m_tiles.at(auxWidth).at(auxHeight).GetSprite().setScale(2, 2);
			m_tiles.at(auxWidth).at(auxHeight).GetSprite().setTextureRect(sf::IntRect(m_tiles.at(auxWidth).at(auxHeight).GetSprite().getPosition().x * 32, m_tiles.at(auxWidth).at(auxHeight).GetSprite().getPosition().y * 32, 32, 32));
			m_tiles.at(auxWidth).at(auxHeight).GetSprite().setPosition(auxWidth * 64 + m_offsetHeight, auxHeight * 64 + m_offsetWidth);
			numberCrates--;
		}

		if (auxHeight == height || auxWidth == width)
		{
			srand(NULL);
		}
	}

	/*for (int indexX = 0; indexX < getSize().x; indexX++)
	{
		for (int indexY = 0; indexY < getSize().y; indexY++)
		{
			std::cout << std::setw(3) << getMapTiles()[indexX][indexY].getType();
		}

		std::cout << std::endl;
	}*/
}

const bool Map::PositionValidator(int width, int height)
{
	if (m_tiles.at(width).at(height).GetType() != 0)
	{
		return false;
	}
	if ((height == 1 && width == 1) || (height == 2 && width == 1) || (height == 1 && width == 2) ||
		(height == GetSize().y - 2 && width == GetSize().x - 2) || (height == GetSize().y - 3 && width == GetSize().x - 2) || (height == GetSize().y - 2 && width == GetSize().x - 3) ||
		(height == GetSize().y - 2 && width == 1) || (height == GetSize().y - 2 && width == 2) || (height == GetSize().y - 3 && width == 1) ||
		(height == 1 && width == GetSize().x - 2) || (height == 2 && GetSize().x - 2) || (height == 1 && width == GetSize().x - 3))
	{
		return false;
	}
	return true;
}

std::vector<std::vector<MapTile>>& Map::GetMapTiles()
{
	return m_tiles;
}

//first is height, second is width
sf::Vector2f Map::GetSize()
{
	return sf::Vector2f(m_width, m_height);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

uint16_t Map::GetCrates()
{
	uint16_t aux = 0;

	for (int indexX = 0; indexX < m_height - 1; indexX++)
	{
		for (uint16_t indexY = 0; indexY < m_width - 1; indexY++)
		{
			if (m_tiles.at(indexX).at(indexY).GetCrate() == true)
			{
				aux++;
			}
		}
	}

	return aux;
}

void Map::DestroyCrate(uint16_t indexX, uint16_t indexY)
{
	if (m_tiles.at(indexX).at(indexY).GetCrate() == true || m_tiles.at(indexX).at(indexY).GetType() == 1)
	{
		m_tiles.at(indexX).at(indexY).SetCrate(false);
		m_tiles.at(indexX).at(indexY).SetType(0);
		m_tiles.at(indexX).at(indexY).GetSprite().setScale(2, 2);
		m_tiles.at(indexX).at(indexY).GetSprite().setTextureRect(sf::IntRect(m_tiles.at(indexX).at(indexY).GetSprite().getPosition().x * 32, m_tiles.at(indexX).at(indexY).GetSprite().getPosition().y * 32, 32, 32));
		m_tiles.at(indexX).at(indexY).SetCoordinates(indexX + m_offsetWidth, indexY + m_offsetHeight);
		m_tiles.at(indexX).at(indexY).GetSprite().setPosition(indexX * 64 + m_offsetHeight, indexY * 64 + m_offsetWidth);
	}
}

void Map::DrawMap(sf::RenderWindow& window)
{
	for (int indexX = 0; indexX < GetSize().x; indexX++)
	{
		for (int indexY = 0; indexY < GetSize().y; indexY++)
		{
			GetMapTiles()[indexX][indexY].Draw(window);
		}
	}
}