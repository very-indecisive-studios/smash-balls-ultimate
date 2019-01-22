#pragma once

#include "core/math.h"
#include "core/graphics/texture.h"
#include <string>

typedef RECT DrawingArea;

class Sprite 
{
protected:
	DrawingArea drawingArea;
private:
	int scale;
	Texture *texture;
	uint8_t layer;
public:
	Sprite(Texture *texture, uint8_t layer, int scale = 1);

	void Draw(Vector2 position);
		
	DrawingArea * GetDrawingArea();
	int GetScale();
	Texture * GetTexture();
	uint8_t GetLayer();

	virtual int GetHeight();
	virtual int GetWidth();

	static Sprite * Create(const std::string &textureName, uint8_t layer, int scale = 1);
};
