#pragma once

#include "ecs/ecs.h"
#include "math/math.h"

struct PositionComponent : public Component
{
	Vector2 pos { };
};
