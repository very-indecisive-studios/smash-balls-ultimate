#include "pch.h"

#include "rendering.h"
#include "game/components/position.h"
#include "game/components/sprite.h"
#include "game/components/animator.h"
#include "context/context.h"

RenderSystem::RenderSystem()
{
	spriteBitset.set(ComponentUtils::GetComponentId<PositionComponent>());
	spriteBitset.set(ComponentUtils::GetComponentId<SpriteComponent>());
	animatorMaskBitset.set(ComponentUtils::GetComponentId<AnimatorComponent>());

	animSpriteBitset.set(ComponentUtils::GetComponentId<PositionComponent>());
	animSpriteBitset.set(ComponentUtils::GetComponentId<SpriteComponent>());
	animSpriteBitset.set(ComponentUtils::GetComponentId<AnimatorComponent>());
}

void RenderSystem::RenderAnimatedSprites()
{

}

void RenderSystem::RenderSprites()
{
	for (auto &entity : *spriteEntities)
	{
		const auto posComp = std::static_pointer_cast<PositionComponent>(entity->GetComponent<PositionComponent>());
		const auto sprComp = std::static_pointer_cast<SpriteComponent>(entity->GetComponent<SpriteComponent>());

		DrawingArea dArea = { 0 };
		dArea.right = sprComp->texture->GetWidth();
		dArea.bottom = sprComp->texture->GetHeight();

		DrawTextureJob *job = new DrawTextureJob
		{
			sprComp->texture,
			sprComp->scale,
			dArea,
			posComp->pos,
			sprComp->layer
		};

		gRenderer->QueueDrawJob(job);
	}
}

void RenderSystem::Process(float deltaTime)
{
	spriteEntities = Context::Get()->GetECSEngine()->GetEntities(spriteBitset, animatorMaskBitset);
	animSpriteEntities = Context::Get()->GetECSEngine()->GetEntities(animSpriteBitset);

	RenderSprites();
}
