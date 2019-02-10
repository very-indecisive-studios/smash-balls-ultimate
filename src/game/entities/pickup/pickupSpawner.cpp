#include <iostream>
#include <ctime>
#include "pch.h"
#include "pickupSpawner.h"
#include "pickup.h"
#include "math/math.h"
#include "game/scenes/game/gameScene.h"
#include "game/resources.h"
#include "constants.h"


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
	int x = rand() % Constants::GAME_WIDTH;
	for (int i = 0; i < TOTAL_PICKUPS_POOLED; i++)
	{

		Pickup *p = nullptr;
		p = new Pickup(Vector2(x, Resources::PICKUP_SPAWNY));
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
	elapsedTime += deltaTime;
	if (elapsedTime >= spawnTime)
	{
		elapsedTime = 0;
	}
}

void PickupSpawner::Reset()
{
	DestroyPool(pickupPool);
}