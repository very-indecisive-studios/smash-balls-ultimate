#include "core/sprites/sprite.h"
#include "core/graphics/graphicsRenderer.h"
#include "context.h"
#include <iostream>

Sprite::Sprite(Texture *texture, uint8_t layer, int scale)
{
	this->texture = texture;
	this->scale = scale;
	this->layer = layer;

	this->drawingArea = { 0 };
	this->drawingArea.right = this->texture->GetWidth();
	this->drawingArea.bottom = this->texture->GetHeight();
}

void Sprite::Draw(Vector2 position)
{
	auto graphicsRenderer
			= Context::Get()->GetGraphicsRenderer();

	DrawTextureJob *job = new DrawTextureJob 
	{
		texture,
		scale,
		drawingArea,
		position,
		layer
	};

	graphicsRenderer->QueueDrawJob(job);
}

Texture * Sprite::GetTexture()
{
	return this->texture;
}

int Sprite::GetHeight()
{
	return this->texture->GetHeight();
}

int Sprite::GetWidth()
{
	return this->texture->GetWidth();
}

int Sprite::GetScale()
{
	return this->scale;
}

DrawingArea * Sprite::GetDrawingArea()
{
	return &(this->drawingArea);
}

Sprite * Sprite::Create(const std::string& textureName, uint8_t layer, int scale)
{
	auto texture 
		= Context::Get()->GetResourceManager()->GetTexture(textureName);

	return new Sprite(texture, layer, scale);
}

uint8_t Sprite::GetLayer()
{
	return layer;
}