#include "AggresiveEnemy.h"
#include "AIEnemy.h"


const float AGRESSIVE_ATTACK_MOVE_PAUSE = 0.25;
const float AGRESSIVE_RUNAWAY_MOVE_PAUSE = 0.15;
const float AGRESSIVE_TIME_IN_SHELTER = 3.5;

void AggresiveEnemy::updateState()
{

	switch(AIEnemy::EnemyState)
	{
	case ATTACKING:
	{
		if (AIEnemy::inDanger()) {
			AIEnemy::goToRunawayState();
			break;
		}
		if (AIEnemy::finishedAttack()) {
			AIEnemy::getState() = REACHED_TARGET;
			break;
		}
		break;
	}

	case REACHED_TARGET:
	{
		if (AIEnemy::inDanger()) {
			AIEnemy::goToRunawayState();
			break;
		}

		AIEnemy::goToAttackState();

		break;
	}

	case RUNAWAY:
	{


	}

	case IN_SHELTER:
	{
		if (AIEnemy::inDanger()) {
			goToRunAwayState();
		}

		if (!AIEnemy::enoughTimeInShelter(AGRESSIVE_TIME_IN_SHELTER)) {
			break;
		}

		else {
			AIEnemy::goToAttackState();
		}

		break;
	}
	}

}

\

AggresiveEnemy::timeToMove()
{
	switch (AIEnemy::getState())
	{
	case ATTACKING:
	{
		return finishedAttack();
		break;
	}

	case RUNAWAY:
	{
		///todo
		break;
	}
	case IN_SHELTER:
	{
		return enoughTimeInShelter();
		break;
	}

	}
}

