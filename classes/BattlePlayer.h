#pragma once

#include "Player.h"

class BattlePlayer : 
	public Player {
private:
	uint16_t m_wins;
	bool m_isDead;

public:
	BattlePlayer();

	void SetWins(int16_t value);
	void SetDead(bool value);

	const uint16_t& GetWins();
	const bool& IsDead();
};