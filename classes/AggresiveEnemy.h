#pragma once
#include "AIEnemy.h"
class AggresiveEnemy :
	public AIEnemy
{
protected:

	void AggresiveEnemy::updateState();
	bool timeToMove();

	

};

