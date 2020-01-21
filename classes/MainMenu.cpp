#include "MainMenu.h"

void drawOptions(sf::RenderWindow& window, uint16_t choice, Text text)
{
	sf::Vector2u windowSize = window.getSize();

	text.getText().setString("BOMBITZAMAN");
	sf::FloatRect textRect = text.getText().getLocalBounds();
	text.getText().setScale(2, 2);
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 4.0f));
	window.draw(text.getText());

	text.getText().setScale(1, 1);
	if (choice == 0)
	{
		text.getText().setString("[ Game Start ]");
	}
	else
	{
		text.getText().setString("Game Start");
	}
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
	window.draw(text.getText());

	if (choice == 1)
	{
		text.getText().setString("[ Battle ]");
	}
	else
	{
		text.getText().setString("Battle");
	}
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + 30));
	window.draw(text.getText());

	if (choice == 2)
	{
		text.getText().setString("[ Setup ]");
	}
	else
	{
		text.getText().setString("Setup");
	}
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + 60));
	window.draw(text.getText());

	if (choice == 3)
	{
		text.getText().setString("[ Password ]");
	}
	else
	{
		text.getText().setString("Password");
	}
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + 90));
	window.draw(text.getText());

	if (choice == 4)
	{
		text.getText().setString("[ Exit ]");
	}
	else
	{
		text.getText().setString("Exit");
	}
	textRect = text.getText().getLocalBounds();
	text.getText().setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text.getText().setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f + 120));
	window.draw(text.getText());
}

void mainMenu(int16_t& gameState, sf::RenderWindow& window, ControlHandler& handler)
{
	uint16_t choice = 0;
	bool isExiting = false;

	sf::Event event;
	sf::Vector2u windowSize;
	sf::View menuView = window.getView();
	sf::Music menuMusic;
	if (!menuMusic.openFromFile(".\\resources\\music\\mainMenu.ogg"))
	{
		std::cout << " +> [ERROR] Main Menu music file NOT found;" << std::endl;
	}
	menuMusic.setVolume(50);
	menuMusic.play();

	window.setKeyRepeatEnabled(false);

	Text text;

	while (gameState == 1 && window.isOpen())
	{
		windowSize = window.getSize();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				menuMusic.stop();
				window.close();
			}

			if ((event.type == sf::Event::KeyPressed || ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) > 0) && handler.GoUp(0))
			{
				if (choice == 0)
				{
					choice = 4;
				}
				else
				{
					choice--;
				}
			}

			if ((event.type == sf::Event::KeyPressed || ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)) < 0) && handler.GoDown(0))
			{
				if (choice == 4)
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
					gameState = 2;
					menuMusic.stop();
					break;
				case 1:
					gameState = 3;
					menuMusic.stop();
					break;
				case 2:
					gameState = 4;
					menuMusic.stop();
					break;
				case 3:
					gameState = 5;
					menuMusic.stop();
					break;
				case 4:
					gameState = 0;
					menuMusic.stop();
					break;
				}
				break;
			}

			if (event.type == sf::Event::Resized)
			{
				if (window.getSize().x < 960)
				{
					window.setSize(sf::Vector2u(960, window.getSize().y));
				}
				if (window.getSize().y < 832)
				{
					window.setSize(sf::Vector2u(window.getSize().x, 832));
				}

				sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		drawOptions(window, choice, text);

		window.display();
		window.clear();
	}

	window.clear();
	window.display();
}