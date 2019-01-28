#include "pch.h"

#include "rendering.h"
#include "game/components/position.h"
#include "game/components/sprite.h"
#include "game/components/animator.h"
#include "game/components/text.h"
#include "context/context.h"

RenderSystem::RenderSystem()
{
	spriteBitset.set(Component::GetComponentId<PositionComponent>());
	spriteBitset.set(Component::GetComponentId<SpriteComponent>());
	animatorMaskBitset.set(Component::GetComponentId<AnimatorComponent>());

	animSpriteBitset.set(Component::GetComponentId<PositionComponent>());
	animSpriteBitset.set(Component::GetComponentId<SpriteComponent>());
	animSpriteBitset.set(Component::GetComponentId<AnimatorComponent>());

	textBitset.set(Component::GetComponentId<PositionComponent>());
	textBitset.set(Component::GetComponentId<TextComponent>());
}

void RenderSystem::RenderText()
{
	for (auto &entity : *textEntities)
	{
		const auto posComp	= entity->GetComponent<PositionComponent>();
		const auto textComp = entity->GetComponent<TextComponent>();

		DrawFontJob *job = new DrawFontJob();
		job->pos = posComp->pos;
		job->text = textComp->text;
		job->font = textComp->font;
		job->layer = textComp->layer;
		job->color = textComp->color;
		job->alignment = DT_LEFT;
		job->drawingArea.top = posComp->pos.y;
		job->drawingArea.left = posComp->pos.x;
		job->drawingArea.bottom = posComp->pos.y + textComp->height;
		job->drawingArea.right = posComp->pos.x + textComp->width;

		Context::GraphicsRenderer()->QueueDrawFontJob(job);
	}
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

		if (animComp->isPlaying)
		{
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
		}

		DrawTextureJob *job = new DrawTextureJob();
		job->pos = posComp->pos;
		job->layer = sprComp->layer;
		job->texture = sprComp->texture;
		job->scale = sprComp->scale;
		job->color = 0xFFFFFFFF;
		job->drawingArea.top = animComp->currentFrameRow * animComp->frameHeight;
		job->drawingArea.left = animComp->currentFrameCol * animComp->frameWidth;
		job->drawingArea.bottom = job->drawingArea.top + animComp->frameHeight;
		job->drawingArea.right = job->drawingArea.left + animComp->frameWidth;

		Context::GraphicsRenderer()->QueueDrawTextureJob(job);
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

		DrawTextureJob *job = new DrawTextureJob();
		job->pos = posComp->pos;
		job->layer = sprComp->layer;
		job->texture = sprComp->texture;
		job->scale = sprComp->scale;
		job->color = 0xFFFFFFFF;
		job->drawingArea.bottom = sprComp->texture->GetHeight();
		job->drawingArea.right = sprComp->texture->GetWidth();

		Context::GraphicsRenderer()->QueueDrawTextureJob(job);
	}
}

void RenderSystem::Process(float deltaTime)
{
	spriteEntities = Context::ECSEngine()->GetEntities(spriteBitset, animatorMaskBitset);
	animSpriteEntities = Context::ECSEngine()->GetEntities(animSpriteBitset);
	textEntities = Context::ECSEngine()->GetEntities(textBitset);

	RenderSprites();
	RenderAnimatedSprites(deltaTime);
	RenderText();
}
