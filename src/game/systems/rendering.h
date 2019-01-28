#pragma once

#include "ecs/ecs.h"
#include "context/context.h"

class RenderSystem : public System
{
private:
	ComponentBitset spriteBitset;
	ComponentBitset animatorMaskBitset;
	ComponentBitset animSpriteBitset;

	std::shared_ptr<EntityList> spriteEntities;
	std::shared_ptr<EntityList> animSpriteEntities;

	void RenderAnimatedSprites(float deltaTime);
	void RenderSprites();
public:
	RenderSystem();

	void Process(float deltaTime) override;
};
