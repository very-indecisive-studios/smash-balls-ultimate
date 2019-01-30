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

	spriteComp->texture = isPlayer1 ? rightOffSpritesheetTexture : leftOffSpritesheetTexture;
	spriteComp->layer = 100;
	animComp->secondsPerFrame = Resources::PLAYER_ANIMATION_DELAY;
	animComp->frameWidth = Resources::PLAYER_WIDTH;
	animComp->frameHeight = Resources::PLAYER_HEIGHT;

	animComp->Play();
}

void Player::Update(float deltaTime)
{
	animComp->Stop();

	if (Context::InputManager()->IsKeyDown(rightKey))
	{
		posComp->pos.x += deltaTime * velocity.x;
		spriteComp->texture = rightOffSpritesheetTexture;
		animComp->Play();
	}
	if (Context::InputManager()->IsKeyDown(leftKey))
	{
		posComp->pos.x += deltaTime * -velocity.x;
		spriteComp->texture = leftOffSpritesheetTexture;
		animComp->Play();
	}

	if (Context::InputManager()->IsKeyDown(jetpackKey))
	{
		if (spriteComp->texture == rightOffSpritesheetTexture)
		{ 
			spriteComp->texture = rightOnSpritesheetTexture;
			animComp->Reset();
			animComp->Play();
		}

		if (spriteComp->texture == leftOffSpritesheetTexture)
		{
			spriteComp->texture = leftOnSpriteheetTexture;
			animComp->Reset();
			animComp->Play();
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

	// player on floor
	if (posComp->pos.y > Constants::GAME_HEIGHT - Resources::PLAYER_HEIGHT - Resources::GROUND_HEIGHT)
	{
		posComp->pos.y = Constants::GAME_HEIGHT - Resources::PLAYER_HEIGHT - Resources::GROUND_HEIGHT;
	}
}