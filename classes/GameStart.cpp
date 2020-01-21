#include "GameStart.h"

const void deathScreen(int16_t& gameState, sf::RenderWindow& window, uint16_t playerLives, uint16_t& livesAux)
{
	sf::Event event;
	sf::Vector2u windowSize;
	sf::Clock timer;

	Text text;
	std::string string;
	sf::FloatRect textRect;

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(".\\resources\\music\\deathSound.ogg"))
	{
		std::cout << " +> [ERROR] Main Menu music file NOT found;" << std::endl;
	}
	sf::Sound deathSound;
	deathSound.setBuffer(buffer);

	window.clear();
	timer.restart();

	windowSize = window.getSize();
	string = "[ Lives " + std::to_string(playerLives + 1) + " ]";
	text.getText().setString(string);
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
	window.draw(text.getText());

	bool next = false;
	while (next == false)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				gameState = 0;
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
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

				textRect = text.getText().getLocalBounds();
				text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
				text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
			}
		}

		windowSize = window.getSize();
		window.draw(text.getText());

		window.display();
		window.clear();

		next = false;
		if (timer.getElapsedTime().asSeconds() >= (float)1)
		{
			next = true;
		}
	}

	deathSound.play();
	next = false;
	window.display();
	window.clear();
	timer.restart();

	if (playerLives != 0)
	{
		string = "[ Lives " + std::to_string(playerLives) + " ]";
	}
	else
	{
		string = "[ Game Over ]";
	}
	text.getText().setString(string);
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
	window.draw(text.getText());

	while (next == false)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				gameState = 0;
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
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

				textRect = text.getText().getLocalBounds();
				text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
				text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
			}
		}

		windowSize = window.getSize();
		window.draw(text.getText());

		window.display();
		window.clear();

		next = false;
		if (timer.getElapsedTime().asSeconds() >= (float)1)
		{
			next = true;
		}
	}

	window.display();
	window.clear();
	livesAux--;
}

void gameStart(int16_t& gameState, sf::RenderWindow& window, ControlHandler& handler, uint64_t highscore)
{
	Player player(sf::Vector2u(4, 20), highscore);
	uint16_t livesAux = player.GetLives();

	Text text;
	std::string string;
	sf::FloatRect textRect;

	sf::Event event;
	sf::Vector2u windowSize;
	sf::Clock timer;

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(".\\resources\\music\\roundSound.ogg"))
	{
		std::cout << " +> [ERROR] Main Menu music file NOT found;" << std::endl;
	}
	sf::Sound roundSound;
	roundSound.setBuffer(buffer);
	roundSound.play();

	window.clear();

	sf::View menuView = window.getDefaultView();
	window.setView(menuView);

	while (gameState % 10 == 2 && player.GetLives() != 0)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				gameState = 0;
				window.close();
			}

			if (event.type == sf::Event::Resized)
			{
				if (window.getSize().x < 960)
				{
					window.setSize(sf::Vector2u(960, window.getSize().y));
				}
				if (window.getSize().y < 896)
				{
					window.setSize(sf::Vector2u(window.getSize().x, 896));
				}

				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		windowSize = window.getSize();

		string = "[ Stage " + std::to_string(player.GetStage()) + " ]";
		text.getText().setString(string);
		textRect = text.getText().getLocalBounds();
		text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
		text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f - textRect.height));
		window.draw(text.getText());

		string = "[ Round " + std::to_string(player.GetRound()) + " ]";
		text.getText().setString(string);
		textRect = text.getText().getLocalBounds();
		text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
		text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + textRect.height));
		window.draw(text.getText());

		if (timer.getElapsedTime().asSeconds() >= (float)2)
		{
			window.clear();
			GameRound round(window, handler, gameState, player);
			window.setView(sf::View(menuView));

			window.display();
			window.clear();

			if (player.GetLives() < livesAux)
			{
				deathScreen(gameState, window, player.GetLives(), livesAux);
			}

			if (player.GetScore() > highscore)
			{
				highscore = player.GetScore();
			}

			timer.restart();
			roundSound.play();
		}

		window.display();
		window.clear();
	}

	if (player.GetLives() == 0)
	{
		gameState = 1;
	}
}