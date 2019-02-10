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
	static const int TOTAL_PICKUPS_POOLED = 16;

	float totalTime = 0;
	float elapsedTime1 = 0;
	float spawnTime = 3.0;

	std::queue<Pickup *> pickupPool;
	void InitializePool(std::queue<Pickup *> &pool);
	void DestroyPool(std::queue<Pickup *> &pool);
	void DestroyPool(std::deque<Pickup *> &pool);
public:
	PickupSpawner();
	void Update(float deltaTime);
};