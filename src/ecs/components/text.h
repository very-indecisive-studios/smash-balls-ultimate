#pragma once

#include <string>
#include "ecs/ecs.h"
#include "graphics/font.h"

typedef int TextAlignment;

namespace TextAlignPosition
{
	constexpr TextAlignment LEFT = DT_LEFT;
	constexpr TextAlignment H_CENTER = DT_CENTER;
	constexpr TextAlignment RIGHT = DT_RIGHT;
	constexpr TextAlignment V_CENTER = DT_VCENTER;
	constexpr TextAlignment TOP = DT_TOP;
	constexpr TextAlignment BOTTOM = DT_BOTTOM;
};

struct TextComponent : public Component
{
	Font *font;
	std::string text;
	int height;
	int width;
	TextAlignment alignment = TextAlignPosition::LEFT;
	int color = 0xFFFFFFFF;
	uint8_t layer = 0;
};
