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
		Pickup *p = new Pickup(Vector2(100, Resources::PICKUP_SPAWNY));
		p->Update(deltaTime);
		elapsedTime = 0;
	}
}