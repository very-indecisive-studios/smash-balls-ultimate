#pragma once

#include "ecs/ecs.h"
#include "context/context.h"

class RenderSystem : public System
{
private:
	ComponentBitset spriteBitset;
	ComponentBitset animatorMaskBitset;
	ComponentBitset animSpriteBitset;
	ComponentBitset textBitset;

	std::shared_ptr<EntityList> spriteEntities;
	std::shared_ptr<EntityList> animSpriteEntities;
	std::shared_ptr<EntityList> textEntities;

	void RenderText();
	void RenderAnimatedSprites(float deltaTime);
	void RenderSprites();
public:
	RenderSystem();

	void Process(float deltaTime) override;
};
