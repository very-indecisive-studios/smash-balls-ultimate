#pragma once

#include "ecs/ecs.h"
#include "math/math.h"

struct PositionComponent : public Component
{
public:
	Vector2 pos { 0.0f, 0.0f };
};
