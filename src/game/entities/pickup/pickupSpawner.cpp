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
		Pickup *p = new Pickup(Vector2(x, Resources::PICKUP_SPAWNY));
		pickups.push(p);
		elapsedTime = 0;
	}
}

void PickupSpawner::Reset()
{
	for (int i=0; i<pickups.size();i++)
	{
		pickups.pop();
	}
}