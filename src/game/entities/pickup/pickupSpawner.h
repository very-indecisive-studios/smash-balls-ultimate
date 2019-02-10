#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include "game/resources.h"
#include "pch.h"
#include "pickup.h"

class PickupSpawner
{
private:
	float totalTime = 0;
	float elapsedTime = 0;
	float spawnTime = 3.0;

	int x = rand() % Constants::GAME_WIDTH;

public:
	PickupSpawner();
	void Update(float deltaTime);
};