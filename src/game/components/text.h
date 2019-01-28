#pragma once

#include <string>
#include "ecs/ecs.h"
#include "graphics/font.h"

typedef int TextAlignment;

namespace TextAlignPosition
{
	const TextAlignment LEFT = DT_LEFT;
	const TextAlignment H_CENTER = DT_CENTER;
	const TextAlignment RIGHT = DT_RIGHT;
	const TextAlignment V_CENTER = DT_VCENTER;
	const TextAlignment TOP = DT_TOP;
	const TextAlignment BOTTOM = DT_BOTTOM;
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
