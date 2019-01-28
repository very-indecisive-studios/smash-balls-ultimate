#include "pch.h"
#include "player.h"
#include "context/context.h"

Player::Player(std::string color, bool isPlayer1)
	: SceneObject(SceneObjectType::PLAYER)
{
	body->AttachComponent<PositionComponent>(posComp);
	body->AttachComponent<SpriteComponent>(spriteComp);
	body->AttachComponent<AnimatorComponent>(animComp);
	Context::ECSEngine()->AttachEntity(body);

	leftOffAnimSprite->Create(Resources::PLAYER_LEFT_OFF_FOLDER + color + ".png", 1, Resources::PLAYER_WIDTH, Resources::PLAYER_HEIGHT, Resources::PLAYER_ANIMATION_DELAY);
	leftOnAnimSprite ->Create(Resources::PLAYER_LEFT_ON_FOLDER + color + ".png", 1, Resources::PLAYER_WIDTH, Resources::PLAYER_HEIGHT, Resources::PLAYER_ANIMATION_DELAY);
	rightOffAnimSprite->Create(Resources::PLAYER_RIGHT_OFF_FOLDER + color + ".png", 1, Resources::PLAYER_WIDTH, Resources::PLAYER_HEIGHT, Resources::PLAYER_ANIMATION_DELAY);
	rightOnAnimSprite->Create(Resources::PLAYER_RIGHT_ON_FOLDER + color + ".png", 1, Resources::PLAYER_WIDTH, Resources::PLAYER_HEIGHT, Resources::PLAYER_ANIMATION_DELAY);

	if (isPlayer1) { currentAnimSprite = rightOffAnimSprite ; }
	else { currentAnimSprite = leftOffAnimSprite; }
}

void Player::Update(float deltaTime)
{
	if (Context::InputManager()->IsKeyDown(rightKey))
	{
		posComp->pos.x += deltaTime * velocity.x;
	}
	if (Context::InputManager()->IsKeyDown(leftKey))
	{
		posComp->pos.x += deltaTime * -velocity.x;
	}

	if (Context::InputManager()->IsKeyDown(jetpackKey))
	{
		if (currentAnimSprite == rightOffAnimSprite)
		{ 
			currentAnimSprite = rightOnAnimSprite; 
		}

		if (currentAnimSprite == leftOffAnimSprite)
		{
			currentAnimSprite = leftOnAnimSprite;
		}
		posComp->pos.y += deltaTime * velocity.y;
	}
	else
	{
		if (currentAnimSprite == rightOnAnimSprite)
		{
			currentAnimSprite = rightOffAnimSprite;
		}

		if (currentAnimSprite == leftOnAnimSprite)
		{
			currentAnimSprite = leftOffAnimSprite;
		}
		posComp->pos.y += deltaTime * -velocity.y;
	}
}