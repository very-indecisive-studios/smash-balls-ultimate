#pragma once

#include "ecs/ecs.h"
#include "graphics/texture.h"
#include "math/math.h"

class SpriteComponent : public Component
{
public:
	float scale = 1.0f;
	Texture *texture = nullptr;
	uint8_t layer = 0;
};
