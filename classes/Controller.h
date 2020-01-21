#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>

class Control {
private:
	unsigned int m_ID;
	unsigned int m_playerNumber;

public:
	Control(unsigned int& ID, unsigned int& playerNumber);

	const unsigned int GetID();

	bool GoUp();
	bool GoDown();
	bool GoLeft();
	bool GoRight();
	bool PressAction();
	bool PressBack();
};

class ControlHandler {
private:
	std::vector<Control> m_players;
	uint16_t m_nrPlayers;

public:
	ControlHandler();

	void AddPlayer(unsigned int m_ID, unsigned int playerNumber);
	Control& GetPlayer(uint16_t PlayerNumber);
	;
	bool PressBack();
	bool GoUp(uint16_t PlayerNumber);
	bool GoDown(uint16_t PlayerNumber);
	bool GoLeft(uint16_t PlayerNumber);
	bool GoRight(uint16_t PlayerNumber);
	bool PressAction(uint16_t PlayerNumber);
	bool PressBack(uint16_t PlayerNumber);
};

//button 0 -> A
//button 1 -> B
//button 2 -> X
//button 3 -> Y
//button 4 -> LB
//button 5 -> RB
//button 6 -> back
//button 7 -> start
//button 8 -> Left
//button 9 -> Right
//axis PovX -> D-Pad left -100 // right 100
//axis PovY -> D-Pad down -100 // up 100