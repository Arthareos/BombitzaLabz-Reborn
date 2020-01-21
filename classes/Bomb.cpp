#include "Bomb.h"

Bomb::Bomb() {}

Bomb::~Bomb() {}

Bomb::Bomb(std::string bombTextureDirectory)
{
	bombNumber = 2;
	size = sf::Vector2f(60.f, 60.f);
	deltaTimeBomb = 0.f;
	explosionDeltaTime = 0.f;
	placedBomb = false;
	explosionSize = 2;
	imageCount = sf::Vector2u(1, 1);
	currentImage = sf::Vector2u(1, 1);
	switchTime = 0.1f;

	if (!texture.loadFromFile(bombTextureDirectory))
	{
		std::cout << " +> [ERROR] Bomb texture NOT loaded;" << std::endl;
	}
	else
	{
		std::cout << " +> [INFO] Bomb texture loaded;" << std::endl;
	}

	sprBomb.setTexture(&texture);

	animationRect.width = texture.getSize().x / float(imageCount.x);
	animationRect.height = texture.getSize().y / float(imageCount.y);

}

void Bomb::placeBomb(Map& map, Player& player, ControlHandler& handler)
{
	if (sf::Event::JoystickButtonPressed && handler.PressAction(0))
	{
		if (map.GetMapTiles()[player.GetPositionOnMap(map).x][player.GetPositionOnMap(map).y].GetBomb() == false)
		{
			if (vecBomb.size() != bombNumber)
			{
				map.GetMapTiles()[player.GetPositionOnMap(map).x][player.GetPositionOnMap(map).y].SetBomb(true);

				sprBomb.setSize(size);
				sprBomb.setPosition(map.GetMapTiles()[player.GetPositionOnMap(map).x][player.GetPositionOnMap(map).y].GetSprite().getPosition().x, map.GetMapTiles()[player.GetPositionOnMap(map).x][player.GetPositionOnMap(map).y].GetSprite().getPosition().y);
				vecBomb.push_back(std::make_pair(sprBomb, deltaTimeBomb));

				position.push_back(player.GetPositionOnMap(map));
			}
		}
	}
}

void Bomb::drawBomb(sf::RenderWindow& window, float deltaTime)
{
	if (!vecBomb.empty())
	{
		//update(deltaTime);

		for (auto bomb : vecBomb)
		{
			window.draw(bomb.first);
		}
	}
}

//creating the positions for the 
void Bomb::explodeCenter(Map& map, Explosion& explosion, int i)
{
	explosion.explVec.at(0).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y].GetSprite().getPosition());
	explosion.explVec.at(0).setSize(sf::Vector2f(80, 80));

	explosionVector.push_back(std::make_pair(explosion.explVec.at(0),deltaTimeBomb));
}

void Bomb::explodeUp(Map& map, Explosion& explosion, int i)
{
	int k = 1;
	int size = explosion.getExplosionSize();
	bool ok = true;

	while (size > 1)
	{
		if (map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y - k].GetType() == 0)
		{
			explosion.explVec.at(1).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y - k].GetSprite().getPosition());
			explosion.explVec.at(1).setSize(sf::Vector2f(80, 80));
			explosionVector.push_back(std::make_pair(explosion.explVec.at(1), deltaTimeBomb));

			size--;
			k++;
		}
		else
		{
			map.DestroyCrate(getBombPositionOnMap(i).x, getBombPositionOnMap(i).y - k);
			ok = false;
			break;
		}
	}
	if (ok)
	{
		if (map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y - explosion.getExplosionSize()].GetType() == 0)
		{
			explosion.explVec.at(3).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y - explosion.getExplosionSize()].GetSprite().getPosition());
			explosion.explVec.at(3).setSize(sf::Vector2f(80, 80));
			explosionVector.push_back(std::make_pair(explosion.explVec.at(3), deltaTimeBomb));
		}
		else
		{
			map.DestroyCrate(getBombPositionOnMap(i).x, getBombPositionOnMap(i).y - explosion.getExplosionSize());
		}
	}
}

void Bomb::explodeDown(Map& map, Explosion& explosion, int i)
{
	int k = 1;
	int size = explosion.getExplosionSize();
	bool ok = true;

	while (size > 1)
	{
		if (map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y + k].GetType() == 0)
		{
			explosion.explVec.at(1).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y + k].GetSprite().getPosition());
			explosion.explVec.at(1).setSize(sf::Vector2f(80, 80));
			explosionVector.push_back(std::make_pair(explosion.explVec.at(1), deltaTimeBomb));

			size--;
			k++;
		}
		else
		{
			map.DestroyCrate(getBombPositionOnMap(i).x, getBombPositionOnMap(i).y + k);
			ok = false;
			break;
		}
	}

	if (ok)
	{
		if (map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y + explosion.getExplosionSize()].GetType() == 0)
		{
			explosion.explVec.at(4).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x][getBombPositionOnMap(i).y + explosion.getExplosionSize()].GetSprite().getPosition());
			explosion.explVec.at(4).setSize(sf::Vector2f(80, 80));
			explosionVector.push_back(std::make_pair(explosion.explVec.at(4), deltaTimeBomb));
		}
		else
		{
			map.DestroyCrate(getBombPositionOnMap(i).x, getBombPositionOnMap(i).y + explosion.getExplosionSize());
		}
	}
}

void Bomb::explodeLeft(Map& map, Explosion& explosion, int i)
{
	int k = 1;
	int size = explosion.getExplosionSize();
	bool ok = true;

	while (size > 1)
	{
		if (map.GetMapTiles()[getBombPositionOnMap(i).x - k][getBombPositionOnMap(i).y].GetType() == 0)
		{
			explosion.explVec.at(2).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x - k][getBombPositionOnMap(i).y].GetSprite().getPosition());
			explosion.explVec.at(2).setSize(sf::Vector2f(80, 80));
			explosionVector.push_back(std::make_pair(explosion.explVec.at(2), deltaTimeBomb));

			size--;
			k++;
		}
		else
		{
			map.DestroyCrate(getBombPositionOnMap(i).x - k, getBombPositionOnMap(i).y);
			ok = false;
			break;
		}
	}

	if (ok)
	{
		if (map.GetMapTiles()[getBombPositionOnMap(i).x - explosion.getExplosionSize()][getBombPositionOnMap(i).y].GetType() == 0)
		{
			explosion.explVec.at(6).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x - explosion.getExplosionSize()][getBombPositionOnMap(i).y].GetSprite().getPosition());
			explosion.explVec.at(6).setSize(sf::Vector2f(80, 80));
			explosionVector.push_back(std::make_pair(explosion.explVec.at(6), deltaTimeBomb));
		}
		else
		{
			map.DestroyCrate(getBombPositionOnMap(i).x - explosion.getExplosionSize(), getBombPositionOnMap(i).y);
		}
	}
}

void Bomb::explodeRight(Map& map, Explosion& explosion, int i)
{
	int k = 1;
	int size = explosion.getExplosionSize();
	bool ok = true;

	while (size > 1)
	{
		if (map.GetMapTiles()[getBombPositionOnMap(i).x + k][getBombPositionOnMap(i).y].GetType() == 0)
		{
			explosion.explVec.at(2).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x + k][getBombPositionOnMap(i).y].GetSprite().getPosition());
			explosion.explVec.at(2).setSize(sf::Vector2f(80, 80));
			explosionVector.push_back(std::make_pair(explosion.explVec.at(2), deltaTimeBomb));

			size--;
			k++;
		}
		else
		{
			map.DestroyCrate(getBombPositionOnMap(i).x + k, getBombPositionOnMap(i).y);
			ok = false;
			break;
		}
	}

	if (ok)
	{
		if (map.GetMapTiles()[getBombPositionOnMap(i).x + explosion.getExplosionSize()][getBombPositionOnMap(i).y].GetType() == 0)
		{
			explosion.explVec.at(5).setPosition(map.GetMapTiles()[getBombPositionOnMap(i).x + explosion.getExplosionSize()][getBombPositionOnMap(i).y].GetSprite().getPosition());
			explosion.explVec.at(5).setSize(sf::Vector2f(80, 80));
			explosionVector.push_back(std::make_pair(explosion.explVec.at(5), deltaTimeBomb));
		}
		else
		{
			map.DestroyCrate(getBombPositionOnMap(i).x + explosion.getExplosionSize(), getBombPositionOnMap(i).y);
		}
	}
}

void Bomb::createExplosion(Map& map, Explosion& explosion, int i)
{
	explodeCenter(map,explosion, i);
	explodeDown(map, explosion, i);
	explodeLeft(map, explosion, i);
	explodeRight(map, explosion, i);
	explodeUp(map, explosion, i);
}

void Bomb::deleteBomb(Map& map,Explosion& explosion, float deltaTime)
{
	if (!vecBomb.empty())
	{
		deltaTimeBomb += deltaTime;

		if (deltaTimeBomb > vecBomb.at(0).second + 3)
		{
			vecBomb.erase(vecBomb.begin());
			createExplosion(map, explosion, 0);
			map.GetMapTiles()[getBombPositionOnMap(0).x][getBombPositionOnMap(0).y].SetBomb(false);
			position.erase(position.begin());
			
		}
	}
}

void Bomb::drawExplosion(sf::RenderWindow& window)
{
	for (auto explozie : explosionVector)
	{
		window.draw(explozie.first);
	}
}

void Bomb::deleteExplosion(float deltaTime)
{
	
	if (!explosionVector.empty())
	{
		deltaTimeBomb += deltaTime;
		if (deltaTimeBomb > explosionVector.at(0).second + 1)
		{
			explosionVector.erase(explosionVector.begin());
		}
	}
}




sf::Vector2u Bomb::getBombPositionOnMap(int i)
{
	return position.at(i);
}

void Bomb::update(float deltaTime)
{
	animationDeltaTime += deltaTime;
	
	if (animationDeltaTime >= switchTime)
	{
		animationDeltaTime -= switchTime;
		currentImage.x++;

		if (currentImage.x > imageCount.x)
		{
			currentImage.x = 1;
		}
	}

	animationRect.left = currentImage.x * animationRect.width;
	animationRect.top = currentImage.y * animationRect.height;

	sprBomb.setSize(size);
	sprBomb.setTextureRect(animationRect);
}

void Bomb::functionality(float& deltaTime, Map& map, sf::RenderWindow& window, ControlHandler& handler, Explosion& explosion, Player& player)
{
	placeBomb(map, player, handler);
	drawBomb(window, deltaTime);
	deleteBomb(map, explosion, deltaTime);
	drawExplosion(window);
	deleteExplosion(deltaTime);
}