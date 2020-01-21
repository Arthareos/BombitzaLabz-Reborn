#include "GamemodeSelector.h"

constexpr auto VERSION = "BombitzaLabz Reborn (Alpha 2.1)";;

void gamemodeSelector()
{
	std::string aux = VERSION;
	std::cout << " +> [INFO] Successfully called \"gamemodeSelector()\";" << std::endl;

	//sf::RenderWindow window(sf::VideoMode::getDesktopMode(), aux, sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(960, 896), aux);
	//sf::RenderWindow window(sf::VideoMode(1000, 1000), aux);

	sf::Event event;

	sf::Image windowIcon;
	if (!windowIcon.loadFromFile(".\\resources\\bombermanBombSprite.png"))
	{
		std::cout << " +> [ERROR] Window icon NOT loaded;" << std::endl;
	}
	window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
	window.setFramerateLimit(60);

	ControlHandler handler;
	sf::Joystick::update();
	if (sf::Joystick::isConnected(0))
	{
		handler.AddPlayer(0, 0);
		std::cout << " +> [INFO] Controller connected;" << std::endl;
	}
	else
	{
		handler.AddPlayer(99, 0);
		std::cout << " +> [INFO] Controller is NOT connected, switching to keyboard input;" << std::endl;
	}

	int16_t gameState = 1;
	uint64_t highscore = 0;

	do {
		switch (gameState)
		{
		case 0:
			window.close();
			break;
		case 1:
			mainMenu(gameState, window, handler);
			break;
		case 2:
			gameStart(gameState, window, handler, highscore);
			break;
		case 3:
			BattleMode(gameState, window, handler);
			gameState = 1;
			break;
		default:
			std::cout << "  +> [ERROR] \"" << gameState << "\" gameState non-existent;" << std::endl;
			gameState = 1;
			break;
		}
	} while (gameState != 0 && window.isOpen());
}