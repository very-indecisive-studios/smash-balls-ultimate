#pragma once

#include "ecs/ecs.h"
#include "graphics/texture.h"
#include "math/math.h"

struct SpriteComponent : Component
{
	int scale = 1;
	Texture *texture = nullptr;
	uint8_t layer = 0;
};
