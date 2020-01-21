#include "Random.h"

int Random::generateRandom(int max) const
{
	int randomNumber = rand();
	float random = (randomNumber % max) + 1;
	
	return (int)random;
}

int Random::generateRandom0(int max) const
{
	int randomNumber = rand();
	float random = (randomNumber % max);

	return (int)random;
}
