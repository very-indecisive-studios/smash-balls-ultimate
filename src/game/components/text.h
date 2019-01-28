#pragma once

#include <string>
#include "ecs/ecs.h"
#include "graphics/font.h"

enum class TextAlignment : int
{
	LEFT = DT_LEFT,
	CENTER = DT_CENTER,
	RIGHT = DT_RIGHT,
	VCENTER = DT_VCENTER,
	TOP = DT_TOP,
	BOTTOM = DT_BOTTOM
};

struct TextComponent : public Component
{
	Font *font;
	std::string text;
	int height;
	int width;
	TextAlignment alignment = TextAlignment::LEFT;
	int color = 0xFFFFFFFF;
	uint8_t layer = 0;
};
