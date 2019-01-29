#include "pch.h"
#include "player.h"
#include "context/context.h"

Player::Player(std::string color, bool isPlayer1)
{
	body->AttachComponent<PositionComponent>(posComp);
	body->AttachComponent<SpriteComponent>(spriteComp);
	body->AttachComponent<AnimatorComponent>(animComp);
	Context::ECSEngine()->AttachEntity(body);

	leftOffSpritesheetTexture	= Context::ResourceManager()->GetTexture(Resources::PLAYER_LEFT_OFF_FOLDER + color + ".png");
	leftOnSpriteheetTexture		= Context::ResourceManager()->GetTexture(Resources::PLAYER_LEFT_ON_FOLDER + color + ".png");
	rightOffSpritesheetTexture	= Context::ResourceManager()->GetTexture(Resources::PLAYER_RIGHT_OFF_FOLDER + color + ".png");
	rightOnSpritesheetTexture	= Context::ResourceManager()->GetTexture(Resources::PLAYER_RIGHT_ON_FOLDER + color + ".png");

	currentSpritesheetTexture = isPlayer1 ? rightOffSpritesheetTexture : leftOffSpritesheetTexture;

	spriteComp->texture =  currentSpritesheetTexture;
	spriteComp->layer = 100;
	animComp->secondsPerFrame = Resources::PLAYER_ANIMATION_DELAY;
	animComp->frameWidth = Resources::PLAYER_WIDTH;
	animComp->frameHeight = Resources::PLAYER_HEIGHT;

	animComp->isPlaying = true;
}

void Player::Update(float deltaTime)
{
	if (Context::InputManager()->IsKeyDown(rightKey))
	{
		posComp->pos.x += deltaTime * velocity.x;
		spriteComp->texture = rightOffSpritesheetTexture;
	}
	if (Context::InputManager()->IsKeyDown(leftKey))
	{
		posComp->pos.x += deltaTime * -velocity.x;
		spriteComp->texture = leftOffSpritesheetTexture;
	}

	if (Context::InputManager()->IsKeyDown(jetpackKey))
	{
		if (spriteComp->texture == rightOffSpritesheetTexture)
		{ 
			spriteComp->texture = rightOnSpritesheetTexture;
			animComp->Reset();
		}

		if (spriteComp->texture == leftOffSpritesheetTexture)
		{
			spriteComp->texture = leftOnSpriteheetTexture;
			animComp->Reset();
		}
		posComp->pos.y += deltaTime * velocity.y;
	}
	else
	{
		if (spriteComp->texture == rightOnSpritesheetTexture)
		{
			spriteComp->texture = rightOffSpritesheetTexture;
			animComp->Reset();
		}

		if (spriteComp->texture == leftOnSpriteheetTexture)
		{
			spriteComp->texture = leftOffSpritesheetTexture;
			animComp->Reset();
		}
		posComp->pos.y += deltaTime * -velocity.y;
	}
}