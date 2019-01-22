#include "animatedSprite.h"
#include "context.h"
#include "core/graphics/texture.h"
#include "math.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(
	Texture *texture, uint8_t layer, int frameWidth, int frameHeight, float secondsPerFrame, int scale
) : Sprite(texture, layer, scale)
{
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->secondsPerFrame = secondsPerFrame;
	
	this->drawingArea = { 0 };
	this->drawingArea.right = this->frameWidth;
	this->drawingArea.bottom = this->frameHeight;

	this->framesPerCol = texture->GetWidth() / frameWidth;
	this->framesPerRow = texture->GetHeight() / frameHeight;
}

void AnimatedSprite::Update(float deltaTime)
{
	if (!isPlaying)
	{
		return;
	}
	
	secondsPassed += deltaTime;

	if (secondsPassed >= secondsPerFrame) 
	{
		secondsPassed = 0;

		NextFrame();
	}
}

void AnimatedSprite::UpdateAndDraw(float deltaTime, Vector2 position) 
{
	Update(deltaTime);

	Sprite::Draw(position);
}

void AnimatedSprite::NextFrame() 
{
	// Next frame.
	if (this->currentFrameCol + 1 == framesPerCol) 
	{
		currentFrameCol = 0;
		
		if (this->currentFrameRow + 1 == framesPerRow)
		{
			currentFrameRow = 0;
		}
		else
		{
			currentFrameRow++;
		}
	}
	else
	{
		currentFrameCol++;
	}

	this->drawingArea.left		= currentFrameCol * frameWidth;
	this->drawingArea.top		= currentFrameRow * frameHeight;
	
	this->drawingArea.right		= (currentFrameCol * frameWidth) + frameWidth;
	this->drawingArea.bottom	= (currentFrameRow * frameHeight) + frameHeight;
}

void AnimatedSprite::Play()
{
	this->isPlaying = true;
}

void AnimatedSprite::Reset()
{
	currentFrameCol = 0;
	currentFrameRow = 0;
}

void AnimatedSprite::Stop()
{
	this->isPlaying = false;
}

int AnimatedSprite::GetHeight()
{
	return this->frameHeight;
}

int AnimatedSprite::GetWidth()
{
	return this->frameWidth;
}

AnimatedSprite * AnimatedSprite::Create(const std::string & textureName, uint8_t layer, int frameWidth, int frameHeight, float secondsPerFrame, int scale)
{
	auto texture
		= Context::Get()->GetResourceManager()->GetTexture(textureName);

	return new AnimatedSprite(texture, layer, frameWidth, frameHeight, secondsPerFrame, scale);
}
