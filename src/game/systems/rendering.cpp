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

void RenderSystem::RenderAnimatedSprites(float deltaTime)
{
	for (auto &entity : *animSpriteEntities)
	{
		const auto posComp		= entity->GetComponent<PositionComponent>();
		const auto sprComp		= entity->GetComponent<SpriteComponent>();
		const auto animComp		= entity->GetComponent<AnimatorComponent>();

		// Initialize the animator based on sprite component.
		if (!animComp->isCallibrated)
		{
			// Reset to 0.
			animComp->secondsPassed = 0;
			animComp->currentFrameCol = 0;
			animComp->currentFrameRow = 0;

			animComp->totalFramesPerCol = sprComp->texture->GetWidth() / animComp->frameWidth;
			animComp->totalFramesPerRow = sprComp->texture->GetHeight() / animComp->frameHeight;

			animComp->isCallibrated = true;
		}

		animComp->secondsPassed += deltaTime;

		if (animComp->secondsPassed >= animComp->secondsPerFrame)
		{
			animComp->secondsPassed = 0;

			if (animComp->currentFrameCol + 1 == animComp->totalFramesPerCol)
			{
				animComp->currentFrameCol = 0;

				if (animComp->currentFrameRow + 1 == animComp->totalFramesPerRow)
				{
					animComp->currentFrameRow = 0;
				}
				else
				{
					animComp->currentFrameRow++;
				}
			}
			else
			{
				animComp->currentFrameCol++;
			}
		}

		DrawingArea dArea = { 0 };
		dArea.left		= animComp->currentFrameCol * animComp->frameWidth;
		dArea.top		= animComp->currentFrameRow * animComp->frameHeight;
		dArea.right		= dArea.left + animComp->frameWidth;
		dArea.bottom	= dArea.top + animComp->frameHeight;

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

void RenderSystem::RenderSprites()
{
	for (auto &entity : *spriteEntities)
	{
		const auto posComp = entity->GetComponent<PositionComponent>();
		const auto sprComp = entity->GetComponent<SpriteComponent>();

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
	spriteEntities = Context::ECSEngine()->GetEntities(spriteBitset, animatorMaskBitset);
	animSpriteEntities = Context::ECSEngine()->GetEntities(animSpriteBitset);

	RenderSprites();
	RenderAnimatedSprites(deltaTime);
}
