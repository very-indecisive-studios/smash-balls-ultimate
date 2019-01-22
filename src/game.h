#pragma once

#include <winnt.h>
#include "core/scene/scene.h"
#include "core/scene/sceneManager.h"

class Game 
{
private:
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timerFreq;

	float deltaTime = 0;

	const float MAX_FRAME_RATE = 60.0f;
	const float MIN_FRAME_RATE = 30.0f;
	const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;
	const float MIN_FRAME_TIME = 1.0f / MAX_FRAME_RATE;

public:
	Game();
	~Game();

	void Initialize();
	void Run();

	float GetDeltaTime();
};
