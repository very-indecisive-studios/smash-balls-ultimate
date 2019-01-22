#include "text.h"
#include "context.h"

Text::Text(const std::string &text, uint8_t layer, int color, int alignment, Font *font)
	: text(text), layer(layer), color(color), alignment(alignment), font(font)
{ }

Text::~Text()
{ 
	delete font;
}

void Text::Draw(Vector2 position)
{
	DrawFontJob *job = new DrawFontJob 
	{
		font,
		text,
		angleDegrees,
		color,
		alignment,
		position,
		layer
	};

	Context::Get()->GetGraphicsRenderer()->QueueDrawJob(job);
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

	Font *font = Context::Get()->GetGraphicsRenderer()->LoadFont(fontName, size, weight, italic);
	return new Text(text, layer, color, alignment, font);
}
