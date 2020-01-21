#include "GameRound.h"

constexpr auto TIMER = 300;

const bool PositionValidator(Map& map, int width, int height)
{
	if (map.GetMapTiles().at(height).at(width).GetType() != 0)
	{
		return false;
	}
	if ((height == 1 && width == 1) || (height == 2 && width == 1) || (height == 1 && width == 2) ||
		(height == map.GetSize().y - 2 && width == map.GetSize().x - 2) || (height == map.GetSize().y - 3 && width == map.GetSize().x - 2) || (height == map.GetSize().y - 2 && width == map.GetSize().x - 3) ||
		(height == map.GetSize().y - 2 && width == 1) || (height == map.GetSize().y - 2 && width == 2) || (height == map.GetSize().y - 3 && width == 1) ||
		(height == 1 && width == map.GetSize().x - 2) || (height == 2 && map.GetSize().x - 2) || (height == 1 && width == map.GetSize().x - 3))
	{
		return false;
	}
	return true;
}

void RandomPosition(std::vector<AIEnemy>& enemies, Map& map)
{
	srand(NULL);

	int index = enemies.size() - 1;
	int auxHeight, auxWidth;
	while (index > -1)
	{
		auxHeight = rand() % (int)map.GetSize().x;
		auxWidth = rand() % (int)map.GetSize().y;

		auxHeight = std::clamp(auxHeight, 1, (int)map.GetSize().x - 1);
		auxWidth = std::clamp(auxWidth, 1, (int)map.GetSize().y - 1);

		if (PositionValidator(map, auxWidth, auxHeight))
		{
			enemies.at(index).SetPosition(sf::Vector2f(auxHeight, auxWidth), map);
			index--;
		}
	}
}

void GetLetterboxView(sf::View& view, sf::RenderWindow& window) {

	float windowRatio = (float)window.getSize().x / (float)window.getSize().y;
	float viewRatio = view.getSize().x / (float)view.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	sizeX = viewRatio / windowRatio;
	posX = (1 - sizeX) / 2.f;
	sizeY = windowRatio / viewRatio;
	posY = (1 - sizeY) / 2.f;

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

bool IsPlayable(Player& player, Scoreboard& scoreboard)
{
	bool ok = true;

	if (scoreboard.GetRemainingTime() == 0)
	{
		ok = false;
	}
	if (player.IsDead())
	{
		ok = false;
	}

	return ok;
}

GameRound::GameRound(sf::RenderWindow& window, ControlHandler& handler, int16_t& gameState, Player& player)
{
	player.SetDead(false);

	Map auxMap(window, 15, 13, Biome::castle);
	//Map auxMap(window, 30, 26, Biome::castle);
	m_map = auxMap;

	Bomb auxBomb(".\\resources\\bombermanBombSprite.png");
	m_bomb = auxBomb;

	Explosion auxExplosion(".\\resources\\explosionTexture.png", sf::Vector2u(7, 4));
	m_explosion = auxExplosion;

	Scoreboard auxScoreboard(m_map, player, player.GetHighscore(), TIMER);
	m_scoreboard = auxScoreboard;

	player.SetPosition(m_map, 0);

	for (int index = 0; index < 10; index++)
	{
		AIEnemy enemy(sf::Vector2u(4, 20));
		m_enemies.push_back(enemy);
	}
	RandomPosition(m_enemies, m_map);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	sf::Event event;
	sf::Clock clock;
	sf::Music levelMusic;

	if (!levelMusic.openFromFile(".\\resources\\music\\basicLevel.ogg"))
	//if (!levelMusic.openFromFile(".\\resources\\music\\powerupLevel.ogg"))
	{
		std::cout << " +> [ERROR] Main Menu music file NOT found;" << std::endl;
	}

	levelMusic.setVolume(50);
	levelMusic.play();

	sf::FloatRect viewport(0.f, 0.f, window.getSize().x, window.getSize().y);

	sf::View playerView(viewport);
	playerView.setSize(960, 896);
	playerView.setCenter(playerView.getSize().x / 2, playerView.getSize().y / 2);
	GetLetterboxView(playerView, window);
	window.setView(playerView);

	while (gameState % 10 == 2 && IsPlayable(player, m_scoreboard))
	{
		float deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				levelMusic.stop();
				gameState = 0;
				window.close();
			}

			if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed) && handler.PressBack(0))
			{
				levelMusic.stop();
				gameState = 1;
			}

			if (event.type == sf::Event::Resized)
			{
				//Sets window minimum size
				if (window.getSize().x != 960)
				{
					window.setSize(sf::Vector2u(960, window.getSize().y));
				}
				if (window.getSize().y != 896)
				{
					window.setSize(sf::Vector2u(window.getSize().x, 896));
				}

				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		m_map.DrawMap(window);

		for (int index = 0; index < m_enemies.size(); index++)
		{
			if (m_enemies.at(index).IsDead() == false)
			{
				m_enemies.at(index).Functionality(deltaTime, m_map, window);
			}
		}

		m_bomb.Functionality(deltaTime, m_map, window, handler.GetPlayer(0), m_explosion, player, m_enemies);		
		player.Functionality(deltaTime, m_map, window, handler.GetPlayer(0));
		m_scoreboard.draw(window, deltaTime);

		//Camera control
		if (!(m_map.GetSize().x * 64 < window.getSize().x && m_map.GetSize().y * 64 < window.getSize().y)) //verific daca mapa este mai mare ca ecranul
		{
			playerView.setCenter(player.GetCenterPosition());
			window.setView(playerView);

			if (playerView.getCenter().x - playerView.getSize().x / 2 < m_map.GetMapTiles().at(0).at(0).GetSprite().getPosition().x)
			{
				playerView.setCenter(m_map.GetMapTiles().at(0).at(0).GetSprite().getPosition().x + window.getSize().x / 2, playerView.getCenter().y);
				window.setView(playerView);
			}
			if (playerView.getCenter().y - playerView.getSize().y / 2  < m_map.GetMapTiles().at(0).at(0).GetSprite().getPosition().y - 64)
			{
				playerView.setCenter(playerView.getCenter().x , m_map.GetMapTiles().at(0).at(0).GetSprite().getPosition().y + window.getSize().y / 2 - 64);
				window.setView(playerView);
			}

			//Colt jos-dreapta
			if ((playerView.getCenter().x + playerView.getSize().x) - playerView.getSize().x / 2 - 64 > m_map.GetMapTiles().at(m_map.GetSize().x - 1).at(m_map.GetSize().y - 1).GetSprite().getPosition().x)
			{
				playerView.setCenter(m_map.GetMapTiles().at(m_map.GetSize().x - 1).at(m_map.GetSize().y - 1).GetSprite().getPosition().x - window.getSize().x / 2 + 64, playerView.getCenter().y);
				window.setView(playerView);
			}
			if ((playerView.getCenter().y + playerView.getSize().y) - playerView.getSize().y / 2 - 64 > m_map.GetMapTiles().at(m_map.GetSize().x - 1).at(m_map.GetSize().y - 1).GetSprite().getPosition().y)
			{
				playerView.setCenter(playerView.getCenter().x, m_map.GetMapTiles().at(m_map.GetSize().x - 1).at(m_map.GetSize().y - 1).GetSprite().getPosition().y - window.getSize().y / 2 + 64);
				window.setView(playerView);
			}
		}

		//Windows update
		window.display();
		window.clear();
	}

	if (IsPlayable(player, m_scoreboard) == false)
	{
		player.SetLives(player.GetLives() - 1);
	}
}

Map& GameRound::GetMap()
{
	return m_map;
}

std::vector<AIEnemy>& GameRound::GetEnemies()
{
	return m_enemies;
}