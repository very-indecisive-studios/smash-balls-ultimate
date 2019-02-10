#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include "game/resources.h"
#include "pickup.h"

class PickupSpawner
{
private:
	static const int TOTAL_PICKUPS_POOLED = 12;

	float totalTime = 0;
	float elapsedTime = 0;
	float spawnTime = 3.0;

	int x = rand() % Constants::GAME_WIDTH;
	std::queue<Pickup *> pickups;

public:
	PickupSpawner();
	void Reset();
	void Update(float deltaTime);
};