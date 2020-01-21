#include "BattleStart.h"

Config::Config() {}

Config::~Config() {}

void Config::SetPlayers(uint16_t number)
{
	this->m_nrPlayers = number;
}

void Config::SetNetworkType(Type type)
{
	this->m_networkType = type;
}

void Config::SetNumberRounds(uint16_t nrRounds)
{
	this->m_nrRounds = nrRounds;
}

const uint16_t& Config::GetNumberOfPlayers()
{
	return m_nrPlayers;
}

const Type& Config::GetNetworkType()
{
	return m_networkType;
}

const uint16_t& Config::GetNumberRounds()
{
	return m_nrRounds;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BattleStart::BattleStart(sf::RenderWindow& window, ControlHandler& handler, int16_t& gameState, std::vector<BattlePlayer>& players)
{
	Map auxMap(window, 15, 13, Biome::castle);
	m_map = auxMap;

	BattleScoreboard auxScoreboard(m_map, players);
	m_scoreboard = auxScoreboard;

	for (uint16_t index = 0; index < players.size(); index++)
	{
		players.at(index).SetPosition(m_map, index);
		players.at(index).SetDead(false);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	sf::Event event;
	sf::Clock clock;
	sf::Music levelMusic;

	if (!levelMusic.openFromFile(".\\resources\\music\\basicLevel.ogg"))
	{
		std::cout << " +> [ERROR] Main Menu music file NOT found;" << std::endl;
	}
	levelMusic.setVolume(50);
	levelMusic.play();

	sf::FloatRect viewport(0.f, 0.f, window.getSize().x, window.getSize().y);
	sf::View playerView(viewport);
	playerView.setSize(960, 896);
	playerView.setCenter(playerView.getSize().x / 2, playerView.getSize().y / 2);
	window.setView(playerView);

	while (isOver(players) == false && gameState != 0)
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
		m_scoreboard.Draw(window, players);
		for (int index = 0; index < players.size(); index++)
		{
			players.at(index).Functionality(deltaTime, m_map, window, handler.GetPlayer(index));
		}

		//Camera setup
		if (!(m_map.GetSize().x * 64 < window.getSize().x && m_map.GetSize().y * 64 < window.getSize().y)) //verific daca mapa este mai mare ca ecranul
		{
			playerView.setCenter(players.at(0).GetCenterPosition());
			window.setView(playerView);

			if (playerView.getCenter().x - playerView.getSize().x / 2 < m_map.GetMapTiles().at(0).at(0).GetSprite().getPosition().x)
			{
				playerView.setCenter(m_map.GetMapTiles().at(0).at(0).GetSprite().getPosition().x + window.getSize().x / 2, playerView.getCenter().y);
				window.setView(playerView);
			}
			if (playerView.getCenter().y - playerView.getSize().y / 2 < m_map.GetMapTiles().at(0).at(0).GetSprite().getPosition().y - 64)
			{
				playerView.setCenter(playerView.getCenter().x, m_map.GetMapTiles().at(0).at(0).GetSprite().getPosition().y + window.getSize().y / 2 - 64);
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


		window.display();
		window.clear();
	}
}

const bool& BattleStart::isOver(std::vector<BattlePlayer>& players)
{
	int aux = 0;

	for (uint16_t index = 0; index < players.size(); index++)
	{
		if (players.at(index).IsDead())
		{
			aux++;
		}
	}

	if (aux == 1)
	{
		return true;
	}
	return false;
}
