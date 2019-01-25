#pragma once

#include "ecs/ecs.h"

struct AnimatorComponent : public Component
{
	float secondsPerFrame = 60.0f;
	bool isPlaying = false;

	int frameWidth = 0;
	int frameHeight = 0;

	int totalFrames = 0;
	int framesPerCol = 0;
	int framesPerRow = 0;
	int currentFrameCol = 0;
	int currentFrameRow = 0;

	float secondsPassed = 0;
};