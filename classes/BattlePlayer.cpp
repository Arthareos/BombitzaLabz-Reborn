#include "BattlePlayer.h"

BattlePlayer::BattlePlayer()
{
	m_wins = 0;
	m_isDead = false;
}

void BattlePlayer::SetWins(int16_t value)
{
	this->m_wins += value;
}

void BattlePlayer::SetDead(bool value)
{
	this->m_isDead = value;
}

const uint16_t& BattlePlayer::GetWins()
{
	return m_wins;
}

const bool& BattlePlayer::IsDead()
{
	return m_isDead;
}