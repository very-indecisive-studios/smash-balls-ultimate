#include "pch.h"

#include "player.h"
#include "context/context.h"
#include "game/data/data.h"
#include "game/layers.h"

Player::PlayerTag::PlayerTag(const std::string &tagTexture)
{
	tagEntity = std::make_shared<Entity>();

	posComp = std::make_shared<PositionComponent>();
	posComp->pos = { 0.0f, 0.0f };
	tagEntity->AttachComponent<PositionComponent>(posComp);

	sprComp = std::make_shared<SpriteComponent>();
	sprComp->layer = Layers::UI_IMAGE;
	sprComp->texture = Context::ResourceManager()->GetTexture(tagTexture);
	sprComp->scale = 0.5f;
	tagEntity->AttachComponent<SpriteComponent>(sprComp);

	Context::ECSEngine()->AttachEntity(tagEntity);
}

void Player::PlayerTag::SetPlayerPosition(Vector2 playerPosition)
{
	posComp->pos = playerPosition + GameSceneData::Tag::TAG_LOCATION_OFFSET;
}

Player::Player(std::string color, bool isPlayer1, Vector2 spawnPt)
	: tag({ isPlayer1 ? Resources::PLAYER_1_TAG : Resources::PLAYER_2_TAG })
{
	body->AttachComponent<PositionComponent>(posComp);
	body->AttachComponent<SpriteComponent>(spriteComp);
	body->AttachComponent<AnimatorComponent>(animComp);
	body->AttachComponent<PhysicsComponent>(phyComp);
	Context::ECSEngine()->AttachEntity(body);

	leftOffSpritesheetTexture	= Context::ResourceManager()->GetTexture(Resources::PLAYER_LEFT_OFF_FOLDER + color + ".png");
	leftOnSpritesheetTexture = Context::ResourceManager()->GetTexture(Resources::PLAYER_LEFT_ON_FOLDER + color + ".png");
	rightOffSpritesheetTexture	= Context::ResourceManager()->GetTexture(Resources::PLAYER_RIGHT_OFF_FOLDER + color + ".png");
	rightOnSpritesheetTexture	= Context::ResourceManager()->GetTexture(Resources::PLAYER_RIGHT_ON_FOLDER + color + ".png");

	spriteComp->texture = isPlayer1 ? rightOffSpritesheetTexture : leftOffSpritesheetTexture;
	spriteComp->layer = 10;

	animComp->secondsPerFrame = Resources::PLAYER_ANIMATION_DELAY;
	animComp->frameWidth = Resources::PLAYER_WIDTH;
	animComp->frameHeight = Resources::PLAYER_HEIGHT;
	animComp->Play();

	posComp->pos = spawnPt;

	phyComp->left = posComp->pos.x;
	phyComp->right = posComp->pos.x + Resources::PLAYER_WIDTH;
	phyComp->top = posComp->pos.y;
	phyComp->bottom = posComp->pos.y + Resources::PLAYER_HEIGHT;
	phyComp->isPassive = false;
	phyComp->velocity = Vector2(Resources::P1_SPEED, -Resources::P1_SPEED);
	phyComp->handleCollision = [this](std::shared_ptr<Entity> e) { this->HandleCollision(e); };
}

void Player::HandleCollision(std::shared_ptr<Entity> e)
{
	const auto otherEntityPhysicsComp = e->GetComponent<PhysicsComponent>();
	const auto otherEntityPosComp = e->GetComponent<PositionComponent>();

	if (otherEntityPhysicsComp->isPassive)
	{
		if (posComp->pos.x <= otherEntityPosComp->pos.x + otherEntityPhysicsComp->right - otherEntityPhysicsComp->left)
		{
			posComp->pos.x = otherEntityPosComp->pos.x + otherEntityPhysicsComp->right - otherEntityPhysicsComp->left;
		}
		
		//// left of game
		//if (posComp->pos.x <= 0)
		//{
		//	posComp->pos.x = 0;
		//}

		//// right of game
		//if (posComp->pos.x >= Constants::GAME_WIDTH - Resources::PLAYER_WIDTH)
		//{
		//	posComp->pos.x = Constants::GAME_WIDTH - Resources::PLAYER_WIDTH;
		//}

		//// top of game
		//if (posComp->pos.y <= 0)
		//{
		//	posComp->pos.y = 0;
		//}

		//// bottom of game
		//if (posComp->pos.y >= Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT - Resources::PLAYER_HEIGHT)
		//{
		//	posComp->pos.y = Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT - Resources::PLAYER_HEIGHT;
		//}
	}
	else
	{
		// other --><-- current
		if (posComp->pos.x > otherEntityPosComp->pos.x)
		{
			posComp->pos.x = phyComp->lastCollidedPos.x + 1;
		}

		// current --><-- other
		else if (posComp->pos.x < otherEntityPosComp->pos.x)
		{
			posComp->pos.x = phyComp->lastCollidedPos.x - 1;
		}

		// other
		//--------
		// current
		else if (posComp->pos.y > otherEntityPosComp->pos.y)
		{
			posComp->pos.y = phyComp->lastCollidedPos.y - 1;
		}

		// current
		//--------
		// other
		else if (posComp->pos.y < otherEntityPosComp->pos.y)
		{
			posComp->pos.y = phyComp->lastCollidedPos.y + 1;
		}
	}
}

void Player::Update(float deltaTime)
{
	phyComp->SetCurrentPos(posComp->pos);
	phyComp->left = posComp->pos.x;
	phyComp->right = posComp->pos.x + Resources::PLAYER_WIDTH;
	phyComp->top = posComp->pos.y;
	phyComp->bottom = posComp->pos.y + Resources::PLAYER_HEIGHT;

	animComp->Stop();

	if (Context::InputManager()->IsKeyDown(rightKey))
	{
		posComp->pos.x += deltaTime * velocity.x;
		spriteComp->texture = rightOffSpritesheetTexture;
		animComp->Play();
	}
	else if (Context::InputManager()->IsKeyDown(leftKey))
	{
		posComp->pos.x += deltaTime * -velocity.x;
		spriteComp->texture = leftOffSpritesheetTexture;
		animComp->Play();
	}
	else
	{
		animComp->Stop();
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
			spriteComp->texture = leftOnSpritesheetTexture;
			animComp->Reset();
			animComp->Play();
		}
		posComp->pos.y += deltaTime * velocity.y * 3;
	}
	else
	{
		if (spriteComp->texture == rightOnSpritesheetTexture)
		{
			spriteComp->texture = rightOffSpritesheetTexture;
			animComp->Reset();
		}

		if (spriteComp->texture == leftOnSpritesheetTexture)
		{
			spriteComp->texture = leftOffSpritesheetTexture;
			animComp->Reset();
		}
	}

	// player on floor
	if (posComp->pos.y > Constants::GAME_HEIGHT - Resources::PLAYER_HEIGHT - Resources::GROUND_HEIGHT)
	{
		posComp->pos.y = Constants::GAME_HEIGHT - Resources::PLAYER_HEIGHT - Resources::GROUND_HEIGHT;
	}

	tag.SetPlayerPosition(posComp->pos);
}