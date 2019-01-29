#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "sprites/animatedSprite.h"
#include "game/components/position.h"
#include "game/components/animator.h"
#include "game/components/sprite.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Button : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	//std::shared_ptr<AnimatorComponent> animComp = std::make_shared<AnimatorComponent>();
	std::shared_ptr<Entity> button = std::make_shared<Entity>();

	bool clickable;
	int height;
	int width;
	bool mouseDown = false;
	bool mouseClicked = false;

public:
	Button(std::string pathToTexture, Vector2 pointToDraw, int height, int width, bool clickable);
	bool MouseOverButton();
	void PerformMouseAction();
	void Update(float deltaTime) override;
};