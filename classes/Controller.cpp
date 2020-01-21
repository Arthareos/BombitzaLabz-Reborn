#include "Controller.h"

Control::Control(unsigned int& ID, unsigned int& playerNumber)
{
	if (ID == 99)
	{
		this->m_ID = 99;
	}
	else
	{
		this->m_ID = ID;
	}
	this->m_playerNumber = playerNumber;
}

const unsigned int Control::GetID()
{
	return m_ID;
}

bool Control::GoUp()
{
	if (GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::getAxisPosition(GetID(), sf::Joystick::Axis::PovY) > 0)
	{
		return true;
	}
	return false;
}

bool Control::GoDown()
{
	if (GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::getAxisPosition(GetID(), sf::Joystick::Axis::PovY) < 0)
	{
		return true;
	}
	return false;
}

bool Control::GoLeft()
{
	if (GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::getAxisPosition(GetID(), sf::Joystick::Axis::PovX) < 0)
	{
		return true;
	}
	return false;
}

bool Control::GoRight()
{
	if (GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::getAxisPosition(GetID(), sf::Joystick::Axis::PovX) > 0)
	{
		return true;
	}
	return false;
}

bool Control::PressAction()
{
	if (GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::isButtonPressed(GetID(), 0))
	{
		return true;
	}
	return false;
}

bool Control::PressBack()
{
	if (GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::isButtonPressed(GetID(), 6) || sf::Joystick::isButtonPressed(GetID(), 1))
	{
		return true;
	}
	return false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ControlHandler::PressBack()
{
	for (auto player : m_players)
	{
		if (player.GetID() == 99)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				return true;
			}
		}
		if (sf::Joystick::isButtonPressed(player.GetID(), 6) || sf::Joystick::isButtonPressed(player.GetID(), 1))
		{
			return true;
		}
	}
	return false;
}

bool ControlHandler::GoUp(uint16_t PlayerNumber)
{
	if (m_players.at(PlayerNumber).GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::getAxisPosition(m_players.at(PlayerNumber).GetID(), sf::Joystick::Axis::PovY) > 0)
	{
		return true;
	}
	return false;
}

bool ControlHandler::GoDown(uint16_t PlayerNumber)
{
	if (m_players.at(PlayerNumber).GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::getAxisPosition(m_players.at(PlayerNumber).GetID(), sf::Joystick::Axis::PovY) < 0)
	{
		return true;
	}
	return false;
}

bool ControlHandler::GoLeft(uint16_t PlayerNumber)
{
	if (m_players.at(PlayerNumber).GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::getAxisPosition(m_players.at(PlayerNumber).GetID(), sf::Joystick::Axis::PovX) < 0)
	{
		return true;
	}
	return false;
}

bool ControlHandler::GoRight(uint16_t PlayerNumber)
{
	if (m_players.at(PlayerNumber).GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::getAxisPosition(m_players.at(PlayerNumber).GetID(), sf::Joystick::Axis::PovX) > 0)
	{
		return true;
	}
	return false;
}

bool ControlHandler::PressAction(uint16_t PlayerNumber)
{
	if (m_players.at(PlayerNumber).GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::isButtonPressed(m_players.at(PlayerNumber).GetID(), 0))
	{
		return true;
	}
	return false;
}

bool ControlHandler::PressBack(uint16_t PlayerNumber)
{
	if (m_players.at(PlayerNumber).GetID() == 99)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return true;
		}
		return false;
	}
	if (sf::Joystick::isButtonPressed(m_players.at(PlayerNumber).GetID(), 6) || sf::Joystick::isButtonPressed(m_players.at(PlayerNumber).GetID(), 1))
	{
		return true;
	}
	return false;
}

ControlHandler::ControlHandler()
{
	m_nrPlayers = 0;
}

void ControlHandler::AddPlayer(unsigned int m_ID, unsigned int playerNumber)
{
	m_players.emplace_back(m_ID, playerNumber);
}

Control& ControlHandler::GetPlayer(uint16_t PlayerNumber)
{
	try {
		return m_players.at(PlayerNumber);
	}
	catch (int e)
	{
		return m_players.at(0);
	}
}
