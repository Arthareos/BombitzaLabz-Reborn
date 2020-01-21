#include "BattleMode.h"

void DrawOptions(sf::RenderWindow& window, uint16_t choice, Text text, std::vector<std::string> options)
{
	sf::Vector2u windowSize = window.getSize();

	text.getText().setString(options.at(0));
	sf::FloatRect textRect = text.getText().getLocalBounds();
	text.getText().setScale(2, 2);
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 4.0f));
	window.draw(text.getText());

	text.getText().setScale(1, 1);
	if (choice == 0)
	{
		text.getText().setString("[ " + options.at(1) + " ]");
	}
	else
	{
		text.getText().setString(options.at(1));
	}
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
	window.draw(text.getText());

	if (choice == 1)
	{
		text.getText().setString("[ " + options.at(2) + " ]");
	}
	else
	{
		text.getText().setString(options.at(2));
	}
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + 30));
	window.draw(text.getText());

	if (choice == 2)
	{
		text.getText().setString("[ " + options.at(3) + " ]");
	}
	else
	{
		text.getText().setString(options.at(3));
	}
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + 60));
	window.draw(text.getText());
}

void ConfigScreen(int16_t& gameState, sf::RenderWindow& window, ControlHandler& handler, Config& config)
{
	uint16_t choice = 0;
	bool isExiting = false;

	sf::Event event;
	sf::Vector2u windowSize;
	sf::View menuView = window.getView();

	window.setKeyRepeatEnabled(false);

	Text text;
	std::vector<std::string> options;
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
			}

			if ((event.type == sf::Event::KeyPressed || ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) > 0) && handler.GoUp(0))
			{
				if (choice == 0)
				{
					choice = 2;
				}
				else
				{
					choice--;
				}
			}

			if ((event.type == sf::Event::KeyPressed || ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) < 0) && handler.GoDown(0))
			{
				if (choice == 2)
				{
					choice = 0;
				}
				else
				{
					choice++;
				}
			}

			if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed) && handler.PressAction(0))
			{
				switch (choice)
				{
				case 0:
					config.SetNetworkType(Type::local);
					next = true;
					break;
				case 1:
					config.SetNetworkType(Type::lan);
					next = true;
					break;
				case 2:
					config.SetNetworkType(Type::internet);
					next = true;
					break;
				}
				break;
			}
		}

		DrawOptions(window, choice, text, std::vector<std::string>({
			std::string("Network Type"),
			std::string("Local"),
			std::string("LAN"),
			std::string("Internet") }));

		window.display();
		window.clear();
	}

	next = false;
	window.display();
	window.clear();

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
			}

			if ((event.type == sf::Event::KeyPressed || ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) > 0) && handler.GoUp(0))
			{
				if (choice == 0)
				{
					choice = 2;
				}
				else
				{
					choice--;
				}
			}

			if ((event.type == sf::Event::KeyPressed || ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) < 0) && handler.GoDown(0))
			{
				if (choice == 2)
				{
					choice = 0;
				}
				else
				{
					choice++;
				}
			}

			if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed) && handler.PressAction(0))
			{
				switch (choice)
				{
				case 0:
					config.SetPlayers(2);
					next = true;
					break;
				case 1:
					config.SetPlayers(3);
					next = true;
					break;
				case 2:
					config.SetPlayers(4);
					next = true;
					break;
				}
				break;
			}
		}

		DrawOptions(window, choice, text, std::vector<std::string>({
			std::string("Number of Players"),
			std::string("2"),
			std::string("3"),
			std::string("4") }));

		window.display();
		window.clear();
	}

	next = false;
	window.display();
	window.clear();

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
			}

			if ((event.type == sf::Event::KeyPressed || ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) > 0) && handler.GoUp(0))
			{
				if (choice == 0)
				{
					choice = 2;
				}
				else
				{
					choice--;
				}
			}

			if ((event.type == sf::Event::KeyPressed || ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) < 0) && handler.GoDown(0))
			{
				if (choice == 2)
				{
					choice = 0;
				}
				else
				{
					choice++;
				}
			}

			if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed) && handler.PressAction(0))
			{
				switch (choice)
				{
				case 0:
					config.SetNumberRounds(1);
					next = true;
					break;
				case 1:
					config.SetNumberRounds(3);
					next = true;
					break;
				case 2:
					config.SetNumberRounds(5);
					next = true;
					break;
				}
				break;
			}
		}

		DrawOptions(window, choice, text, std::vector<std::string>({
			std::string("Number of Rounds"),
			std::string("1"),
			std::string("3"),
			std::string("5") }));

		window.display();
		window.clear();
	}
}

void DrawLeaderboard(sf::RenderWindow& window, Text text, std::vector<BattlePlayer> players)
{
	sf::Vector2u windowSize = window.getSize();

	text.getText().setString("Leaderboard");
	sf::FloatRect textRect = text.getText().getLocalBounds();
	text.getText().setScale(2, 2);
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 4.0f));
	window.draw(text.getText());

	text.getText().setScale(1, 1);
	for (uint16_t index = 0; index < players.size(); index++)
	{
		int auxInt = index + 1;
		std::string aux("[ Player " + std::to_string(auxInt) + " / " + std::to_string((int)players.at(index).GetWins()) + std::string(" Wins ]"));
		text.getText().setString(aux);
		textRect = text.getText().getLocalBounds();
		text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
		text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + 30 * index));
		window.draw(text.getText());
	}
}

void BattleMode(int16_t& gameState, sf::RenderWindow& window, ControlHandler& handler)
{
	Config config;
	ConfigScreen(gameState, window, handler, config);

	std::vector<BattlePlayer> battlePlayers;
	for (uint16_t index = 0; index < config.GetNumberOfPlayers(); index++)
	{
		battlePlayers.emplace_back();
	}

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

	sf::View menuView = window.getDefaultView();
	window.setView(menuView);

	//controllers setup
	sf::Joystick::update();
	if (handler.GetPlayer(0).GetID() == NULL)
	{
		for (int index = 0; index < config.GetNumberOfPlayers() - 1; index++)
		{
			handler.AddPlayer(index, index);
		}
	}
	else
	{
		for (int index = 1; index < config.GetNumberOfPlayers(); index++)
		{
			handler.AddPlayer(index, index);
		}
	}

	uint16_t playedRounds = 0;
	while (playedRounds < config.GetNumberRounds() && gameState != 0)
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

		DrawLeaderboard(window, text, battlePlayers);

		if (timer.getElapsedTime().asSeconds() >= (float)2)
		{
			window.clear();
			BattleStart(window, handler, gameState, battlePlayers);
			playedRounds++;
		}

		window.display();
		window.clear();
	}
}