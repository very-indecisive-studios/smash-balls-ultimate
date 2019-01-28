#include "pch.h"

#include "text.h"
#include "context/context.h"

Text::Text(const std::string &text, uint8_t layer, int color, int alignment, Font *font)
	: text(text), layer(layer), color(color), alignment(alignment), font(font)
{ }

Text::~Text()
{ 
	delete font;
}

void Text::Draw(Vector2 position)
{
	DrawFontJob *job = new DrawFontJob();
	job->pos = position;
	job->text = text;
	job->font = font;
	job->layer = layer;
	job->color = color;
	job->drawingArea.top = position.y;
	job->drawingArea.left = position.x;
	job->drawingArea.bottom = 720;
	job->drawingArea.right = 1280;

	Context::GraphicsRenderer()->QueueDrawFontJob(job);
}

void Text::SetText(const std::string& text)
{
	this->text = text;
}

const std::string Text::GetText()
{
	return this->text;
}

int Text::GetColor()
{
	return this->color;
}

void Text::SetColor(int color)
{
	this->color = color;
}

Font * Text::GetFont()
{
	return this->font;
}

float Text::GetAngleDegrees()
{
	return this->angleDegrees;
}

Text * Text::Create(
	const std::string& text,
	const std::string& fontName,
	int color,
	uint8_t size,
	uint8_t layer,
	bool bold,
	bool italic,
	int alignment
)
{
	UINT weight = FW_NORMAL;
	if (bold) 
	{
		weight = weight | FW_BOLD;
	}

	FontConfig config;
	config.height = size;
	config.weight = weight;
	config.italic = italic;

	Font *font = Context::GraphicsRenderer()->LoadFont(fontName, config);
	return new Text(text, layer, color, alignment, font);
}
