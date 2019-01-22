#pragma once

#include "sprite.h"

class AnimatedSprite : public Sprite 
{
private:
	float secondsPerFrame = 60.0f;
	bool isPlaying = false;

	int frameWidth;
	int frameHeight;
		
	int totalFrames;
	int framesPerCol;
	int framesPerRow;
	int currentFrameCol = 0;
	int currentFrameRow = 0;

	float secondsPassed = 0;

	void NextFrame();
public:
	AnimatedSprite(Texture *texture, uint8_t layer, int frameWidth, int frameHeight, float secondsPerFrame, int scale = 1);
	void Update(float deltaTime);
	void UpdateAndDraw(float deltaTime, Vector2 position);
	void Play();
	void Reset();
	void Stop();
	
	int GetHeight() override;
	int GetWidth() override;

	static AnimatedSprite * Create(const std::string &textureName, uint8_t layer, int frameWidth, int frameHeight, float secondsPerFrame, int scale = 1);
};
