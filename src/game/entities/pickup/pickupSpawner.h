#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include "game/resources.h"
#include "pch.h"
#include "pickup.h"
#include "math/math.h"
#include "constants.h"

class PickupSpawner
{
private:
	float totalTime = 0;
	float elapsedTime = 0;
	float spawnTime = 3.0;
	float pickupTime = -1;
	std::vector<Pickup*>pickups;
	int x = rand() % 100;

public:
	PickupSpawner();
	void Reset();
	void Update(float deltaTime);
};