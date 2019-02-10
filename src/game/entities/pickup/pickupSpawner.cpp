#include <iostream>
#include <ctime>
#include "pickupSpawner.h"
#include "pickup.h"
#include "math/math.h"
#include "game/scenes/game/gameScene.h"


PickupSpawner::PickupSpawner()
{
	srand(time(nullptr));

	/*
	 * Initialize pickup pool.
	 */
	InitializePool(pickupPool);

}

PickupSpawner::~PickupSpawner()
{
	DestroyPool(pickupPool);
}


void PickupSpawner::InitializePool(std::queue<Pickup*>& pool)
{
	for (int i = 0; i < TOTAL_PICKUPS_POOLED; i++)
	{
		int x = rand() % 3;

		Pickup *p = nullptr;
		p = new Pickup(3);
		pool.push(p);
	}
}

void PickupSpawner::DestroyPool(std::queue<Pickup*>& pool)
{
	while (!pool.empty())
	{
		delete pool.front();
		pool.pop();
	}
}

void PickupSpawner::DestroyPool(std::deque<Pickup*>& pool)
{
	while (!pool.empty())
	{
		delete pool.front();
		pool.pop_front();
	}
}

void PickupSpawner::Update(float deltaTime)
{
	totalTime += deltaTime;

	if (totalTime >= 15)
	{
		spawnTime -= 0.2;
		totalTime = 0;
	}
	elapsedTime1 += deltaTime;
	if (elapsedTime1 >= spawnTime)
	{
		elapsedTime1 = 0;
	}
}