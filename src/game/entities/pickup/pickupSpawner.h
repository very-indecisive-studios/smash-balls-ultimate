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

	int x = rand() % 1280;

public:
	PickupSpawner();
	void Update(float deltaTime);
};