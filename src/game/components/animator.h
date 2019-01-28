#pragma once

#include "ecs/ecs.h"

struct AnimatorComponent : public Component
{
	float secondsPerFrame = 1.0f;
	bool isPlaying = false;
	int frameWidth = 0;
	int frameHeight = 0;

	void Reset()
	{
		this->isCallibrated = false;
	}

private:
	int totalFramesPerCol = 0;
	int totalFramesPerRow = 0;
	int currentFrameCol = 0;
	int currentFrameRow = 0;
	float secondsPassed = 0;

	bool isCallibrated = false;

	friend class RenderSystem;
};