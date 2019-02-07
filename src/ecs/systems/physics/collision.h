#pragma once

#include <bitset>

namespace CollisionLocation
{
	constexpr uint8_t LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3;
};

typedef std::bitset<4> CollisionResult;
