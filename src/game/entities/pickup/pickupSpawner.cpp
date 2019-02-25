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

void PickupSpawner::Reset() 
{
	for (int i = 0; i < pickups.size(); i++) 
	{
		delete pickups[i];
	}
}

void PickupSpawner::Update(float deltaTime)
{
	for (int i = 0; i < pickups.size(); i++)
	{
		bool isCollided = pickups[i]->CheckCollided();
		if(isCollided)
		{
			delete pickups[i];
			pickups.erase(pickups.begin() + i);
			pickupTime = 7.0;
		}
		if (pickupTime >= 0)
		{
			pickupTime -= deltaTime;
		}
		else
		{
			pickups[i]->ResetPlayer(false);
			pickupTime = -1;
		}
	}
	totalTime += deltaTime;

	if (totalTime >= 15)
	{
		spawnTime -= 0.2;
		totalTime = 0;
	}
	elapsedTime += deltaTime;
	if (elapsedTime >= spawnTime)
	{
		if (pickups.size() >= 3.0) 
		{
			elapsedTime = 0;
		}
		else
		{
			Pickup *p = new Pickup(Vector2(x, Resources::PICKUP_SPAWNY));
			pickups.push_back(p);
			p->Update(deltaTime);
			elapsedTime = 0;
		}
	}
}