#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "game/components/position.h"
#include "game/components/text.h"
#include <memory>
#include <functional>
#include "math/math.h"
#include "game/resources.h"

class TextObject : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<TextComponent> txtComp = std::make_shared<TextComponent>();
	std::shared_ptr<Entity> textEntity = std::make_shared<Entity>();

	bool hoverable;
	std::function<void()> callbackHovered;
	FontConfig fontConfig;

public:
	TextObject(std::string pathToFont, 
		Vector2 pointToDraw, 
		std::string text, 
		int drawingAreaHeight, 
		int drawingAreaWidth, 
		TextAlignment alignment, 
		int fontSize, 
		int color,
		bool hoverable,
		std::function<void()> callbackHovered);

	void SetText(std::string text);
	void ChangeColor(int color);
	void Update(float deltaTime) override;
};