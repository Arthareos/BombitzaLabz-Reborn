#include "Bomb.h"

Bomb::Bomb(std::string bombTextureDirectory)
{
	m_bombNumber = 1;
	m_size = sf::Vector2f(60.f, 60.f);
	m_deltaTimeBomb = 0.f;
	m_explosionSize = 1;

	if (!m_texture.loadFromFile(bombTextureDirectory))
	{
		std::cout << " +> [ERROR] Bomb texture NOT loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Bomb texture loaded;" << std::endl;
	}

	m_sprite.setTexture(&m_texture);
}

void Bomb::PlaceBomb(Map& map, Player& player, Control& control)
{
	if (sf::Event::JoystickButtonPressed && control.PressAction())
	{
		if (map.GetMapTiles()[player.GetPositionOnMap(map).x][player.GetPositionOnMap(map).y].HasBomb() == false)
		{
			if (m_vectorBombs.size() != m_bombNumber)
			{
				player.ResetImmunity();
				map.GetMapTiles()[player.GetPositionOnMap(map).x][player.GetPositionOnMap(map).y].SetBomb(true);

				m_sprite.setSize(m_size);
				m_sprite.setPosition(map.GetMapTiles()[player.GetPositionOnMap(map).x][player.GetPositionOnMap(map).y].GetSprite().getPosition().x, map.GetMapTiles()[player.GetPositionOnMap(map).x][player.GetPositionOnMap(map).y].GetSprite().getPosition().y);
				m_vectorBombs.push_back(std::make_pair(m_sprite, m_deltaTimeBomb));

				m_position.push_back(player.GetPositionOnMap(map));
			}
		}
	}
}

void Bomb::DrawBomb(sf::RenderWindow& window, float deltaTime)
{
	if (!m_vectorBombs.empty())
	{
		for (auto bomb : m_vectorBombs)
		{
			window.draw(bomb.first);
		}
	}
}

//creating the positions for the 
void Bomb::ExplodeCenter(Map& map, Player& player, Explosion& explosion, std::vector<AIEnemy>& enemies, int i)
{
	explosion.GetExplosionsVector().at(0).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y].GetSprite().getPosition());
	explosion.GetExplosionsVector().at(0).setSize(sf::Vector2f(80, 80));

	m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(0), m_deltaTimeBomb));

	if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y))
	{
		player.SetDead(true);
	}
	
	for (int index = 0; index < enemies.size() - 1; index++)
	{
		if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y))
		{
			enemies.at(index).SetDead(true);
		}
	}
}

void Bomb::ExplodeUp(Map& map, Player& player, Explosion& explosion, std::vector<AIEnemy>& enemies, int i)
{
	int k = 1;
	int size = explosion.GetExplosionSize();
	bool ok = true;

	while (size > 1)
	{
		if (map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y - k].GetType() == 0)
		{
			explosion.GetExplosionsVector().at(1).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y - k].GetSprite().getPosition());
			explosion.GetExplosionsVector().at(1).setSize(sf::Vector2f(80, 80));
			m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(1), m_deltaTimeBomb));

			if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y - k))
			{
				player.SetDead(true);
			}

			for (int index = 0; index < enemies.size() - 1; index++)
			{
				if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y - k))
				{
					enemies.at(index).SetDead(true);
				}
			}

			size--;
			k++;
		}
		else
		{
			map.DestroyCrate(GetPositionOnMap(i).x, GetPositionOnMap(i).y - k);
			ok = false;
			break;
		}
	}
	if (ok)
	{
		if (map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y - explosion.GetExplosionSize()].GetType() == 0)
		{
			explosion.GetExplosionsVector().at(3).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y - explosion.GetExplosionSize()].GetSprite().getPosition());
			explosion.GetExplosionsVector().at(3).setSize(sf::Vector2f(80, 80));
			m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(3), m_deltaTimeBomb));

			if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y - k))
			{
				player.SetDead(true);
			}

			for (int index = 0; index < enemies.size() - 1; index++)
			{
				if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y - k))
				{
					enemies.at(index).SetDead(true);
				}
			}
		}
		else
		{
			map.DestroyCrate(GetPositionOnMap(i).x, GetPositionOnMap(i).y - explosion.GetExplosionSize());
		}
	}
}

void Bomb::ExplodeDown(Map& map, Player& player, Explosion& explosion, std::vector<AIEnemy>& enemies, int i)
{
	int k = 1;
	int size = explosion.GetExplosionSize();
	bool ok = true;

	while (size > 1)
	{
		if (map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y + k].GetType() == 0)
		{
			explosion.GetExplosionsVector().at(1).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y + k].GetSprite().getPosition());
			explosion.GetExplosionsVector().at(1).setSize(sf::Vector2f(80, 80));
			m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(1), m_deltaTimeBomb));

			if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y + k))
			{
				player.SetDead(true);
			}

			for (int index = 0; index < enemies.size() - 1; index++)
			{
				if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y + k))
				{
					enemies.at(index).SetDead(true);
				}
			}

			size--;
			k++;
		}
		else
		{
			map.DestroyCrate(GetPositionOnMap(i).x, GetPositionOnMap(i).y + k);
			ok = false;
			break;
		}
	}

	if (ok)
	{
		if (map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y + explosion.GetExplosionSize()].GetType() == 0)
		{
			explosion.GetExplosionsVector().at(4).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x][GetPositionOnMap(i).y + explosion.GetExplosionSize()].GetSprite().getPosition());
			explosion.GetExplosionsVector().at(4).setSize(sf::Vector2f(80, 80));
			m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(4), m_deltaTimeBomb));

			if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y + k))
			{
				player.SetDead(true);
			}

			for (int index = 0; index < enemies.size() - 1; index++)
			{
				if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x, GetPositionOnMap(i).y + k))
				{
					enemies.at(index).SetDead(true);
				}
			}
		}
		else
		{
			map.DestroyCrate(GetPositionOnMap(i).x, GetPositionOnMap(i).y + explosion.GetExplosionSize());
		}
	}
}

void Bomb::ExplodeLeft(Map& map, Player& player, Explosion& explosion, std::vector<AIEnemy>& enemies, int i)
{
	int k = 1;
	int size = explosion.GetExplosionSize();
	bool ok = true;

	while (size > 1)
	{
		if (map.GetMapTiles()[GetPositionOnMap(i).x - k][GetPositionOnMap(i).y].GetType() == 0)
		{
			explosion.GetExplosionsVector().at(2).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x - k][GetPositionOnMap(i).y].GetSprite().getPosition());
			explosion.GetExplosionsVector().at(2).setSize(sf::Vector2f(80, 80));
			m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(2), m_deltaTimeBomb));

			if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x - k, GetPositionOnMap(i).y))
			{
				player.SetDead(true);
			}

			for (int index = 0; index < enemies.size() - 1; index++)
			{
				if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x - k, GetPositionOnMap(i).y))
				{
					enemies.at(index).SetDead(true);
				}
			}

			size--;
			k++;
		}
		else
		{
			map.DestroyCrate(GetPositionOnMap(i).x - k, GetPositionOnMap(i).y);
			ok = false;
			break;
		}
	}

	if (ok)
	{
		if (map.GetMapTiles()[GetPositionOnMap(i).x - explosion.GetExplosionSize()][GetPositionOnMap(i).y].GetType() == 0)
		{
			explosion.GetExplosionsVector().at(6).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x - explosion.GetExplosionSize()][GetPositionOnMap(i).y].GetSprite().getPosition());
			explosion.GetExplosionsVector().at(6).setSize(sf::Vector2f(80, 80));
			m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(6), m_deltaTimeBomb));

			if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x - k, GetPositionOnMap(i).y))
			{
				player.SetDead(true);
			}

			for (int index = 0; index < enemies.size() - 1; index++)
			{
				if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x - k, GetPositionOnMap(i).y))
				{
					enemies.at(index).SetDead(true);
				}
			}
		}
		else
		{
			map.DestroyCrate(GetPositionOnMap(i).x - explosion.GetExplosionSize(), GetPositionOnMap(i).y);
		}
	}
}

void Bomb::ExplodeRight(Map& map, Player& player, Explosion& explosion, std::vector<AIEnemy>& enemies, int i)
{
	int k = 1;
	int size = explosion.GetExplosionSize();
	bool ok = true;

	while (size > 1)
	{
		if (map.GetMapTiles()[GetPositionOnMap(i).x + k][GetPositionOnMap(i).y].GetType() == 0)
		{
			explosion.GetExplosionsVector().at(2).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x + k][GetPositionOnMap(i).y].GetSprite().getPosition());
			explosion.GetExplosionsVector().at(2).setSize(sf::Vector2f(80, 80));
			m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(2), m_deltaTimeBomb));

			if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x + k, GetPositionOnMap(i).y))
			{
				player.SetDead(true);
			}

			for (int index = 0; index < enemies.size() - 1; index++)
			{
				if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x + k, GetPositionOnMap(i).y))
				{
					enemies.at(index).SetDead(true);
				}
			}

			size--;
			k++;
		}
		else
		{
			map.DestroyCrate(GetPositionOnMap(i).x + k, GetPositionOnMap(i).y);
			ok = false;
			break;
		}
	}

	if (ok)
	{
		if (map.GetMapTiles()[GetPositionOnMap(i).x + explosion.GetExplosionSize()][GetPositionOnMap(i).y].GetType() == 0)
		{
			explosion.GetExplosionsVector().at(5).setPosition(map.GetMapTiles()[GetPositionOnMap(i).x + explosion.GetExplosionSize()][GetPositionOnMap(i).y].GetSprite().getPosition());
			explosion.GetExplosionsVector().at(5).setSize(sf::Vector2f(80, 80));
			m_explosionsVector.push_back(std::make_pair(explosion.GetExplosionsVector().at(5), m_deltaTimeBomb));

			if (player.GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x + k, GetPositionOnMap(i).y))
			{
				player.SetDead(true);
			}

			for (int index = 0; index < enemies.size() - 1; index++)
			{
				if (enemies.at(index).GetPositionOnMap(map) == sf::Vector2u(GetPositionOnMap(i).x + k, GetPositionOnMap(i).y))
				{
					enemies.at(index).SetDead(true);
				}
			}
		}
		else
		{
			map.DestroyCrate(GetPositionOnMap(i).x + explosion.GetExplosionSize(), GetPositionOnMap(i).y);
		}
	}
}

void Bomb::CreateExplosion(Map& map, Player& player, Explosion& explosion, std::vector<AIEnemy>& enemies, int i)
{
	ExplodeCenter(map, player, explosion, enemies, i);
	ExplodeDown(map, player, explosion, enemies, i);
	ExplodeLeft(map, player, explosion, enemies, i);
	ExplodeRight(map, player, explosion, enemies, i);
	ExplodeUp(map, player, explosion, enemies, i);
}

void Bomb::DeleteBomb(Map& map, Player& player, Explosion& explosion, std::vector<AIEnemy>& enemies, float deltaTime)
{
	if (!m_vectorBombs.empty())
	{
		m_deltaTimeBomb += deltaTime;

		if (m_deltaTimeBomb > m_vectorBombs.at(0).second + 3)
		{
			m_vectorBombs.erase(m_vectorBombs.begin());
			CreateExplosion(map, player, explosion, enemies, 0);
			map.GetMapTiles()[GetPositionOnMap(0).x][GetPositionOnMap(0).y].SetBomb(false);
			m_position.erase(m_position.begin());
		}
	}
}

void Bomb::DrawExplosion(sf::RenderWindow& window)
{
	for (auto explosion : m_explosionsVector)
	{
		window.draw(explosion.first);
	}
}

void Bomb::DeleteExplosion(float deltaTime)
{
	if (!m_explosionsVector.empty())
	{
		m_deltaTimeBomb += deltaTime;
		if (m_deltaTimeBomb > m_explosionsVector.at(0).second + 1)
		{
			m_explosionsVector.erase(m_explosionsVector.begin());
		}
	}
}

void Bomb::Functionality(float& deltaTime, Map& map, sf::RenderWindow& window, Control& control, Explosion& explosion, Player& player, std::vector<AIEnemy>& enemies)
{
	PlaceBomb(map, player, control);
	DrawBomb(window, deltaTime);
	DeleteBomb(map, player, explosion, enemies, deltaTime);
	DrawExplosion(window);
	DeleteExplosion(deltaTime);
}