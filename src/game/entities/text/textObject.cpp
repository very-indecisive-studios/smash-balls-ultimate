#include "pch.h"
#include "textObject.h"
#include "context/context.h"

TextObject::TextObject(std::string fontName, 
	Vector2 pointToDraw, 
	std::string text, 
	int drawingAreaHeight, 
	int drawingAreaWidth, 
	TextAlignment alignment, 
	int fontSize, 
	int color,
	bool hoverable,
	std::function<void()> callbackHovered)
{
	textEntity->AttachComponent<PositionComponent>(posComp);
	textEntity->AttachComponent<TextComponent>(txtComp);
	Context::ECSEngine()->AttachEntity(textEntity);

	txtComp->text = text;
	txtComp->height = drawingAreaHeight;
	txtComp->width = drawingAreaWidth;
	fontConfig.height = fontSize;
	txtComp->font = Context::ResourceManager()->GetFont(fontName, fontConfig);
	txtComp->alignment = alignment;
	txtComp->color = color;
	txtComp->layer = 100;
	posComp->pos = pointToDraw;

	this->hoverable = hoverable;
	this->callbackHovered = callbackHovered;
}

void TextObject::SetText(std::string text)
{
	txtComp->text = text;
}

void TextObject::ChangeColor(int color) 
{
	txtComp->color = color;
}

void TextObject::Update(float deltaTime)
{
	if (hoverable) 
	{
		callbackHovered();
	}
}