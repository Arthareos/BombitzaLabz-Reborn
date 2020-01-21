#include "Controller.h"

Control::Control()
{
	this->m_ID = 99;
}

Control::Control(unsigned int m_ID)
{
	this->m_ID = m_ID;
}

const unsigned int Control::GetID()
{
	return m_ID;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

void ControlHandler::AddPlayer()
{
	m_players.emplace_back(99);
}

void ControlHandler::AddPlayer(unsigned int m_ID)
{
	m_players.emplace_back(m_ID);
}

Control& ControlHandler::getPlayer(uint16_t PlayerNumber)
{
	try {
		return m_players.at(PlayerNumber);
	}
	catch (int e)
{
		return m_players.at(0);
	}
}
