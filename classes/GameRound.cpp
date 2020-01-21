#include "GameRound.h"

constexpr auto TIMER = 300;

void getLetterboxView(sf::View& view, sf::RenderWindow& window) {

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

GameRound::GameRound(sf::RenderWindow& window, ControlHandler& handler, int16_t& gameState, Player& player)
{
	Map auxMap(window, 15, 13, Biome::castle);
	//Map auxMap(window, 30, 26, Biome::castle);
	m_map = auxMap;

	Bomb auxBomb(".\\resources\\bombermanBombSprite.png");
	m_bomb = auxBomb;

	Explosion auxExplosion(".\\resources\\explosionTexture.png", sf::Vector2u(7, 4));
	m_explosion = auxExplosion;

	//aiEnemies.emplace_back(".\\resources\\enemy.png", sf::Vector2u(4, 20), 0.1f, 100.0f);

	Scoreboard auxScoreboard(m_map, player, TIMER);
	m_scoreboard = auxScoreboard;

	player.SetPosition(m_map, 0);
	
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
	getLetterboxView(playerView, window);
	window.setView(playerView);

	while (gameState % 10 == 2 && m_scoreboard.GetRemainingTime() != 0)
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

		/*for (int index = 0; index < aiEnemies.size(); index++)
		{
			m_enemies.at(index).Update(map, deltaTime, window);
		}*/

		m_bomb.placeBomb(m_map, player, handler);
		m_bomb.drawBomb(window, deltaTime);
		m_bomb.deleteBomb(m_map, m_explosion, deltaTime);
		m_bomb.drawExplosion(window);
		m_bomb.deleteExplosion(deltaTime);
		
		player.Functionality(deltaTime, m_map, window, handler.GetPlayer(0));

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

		m_scoreboard.draw(window, deltaTime);

		//Windows update
		window.display();
		window.clear();
	}

	if (m_scoreboard.GetRemainingTime() < 1)
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