#pragma once
#include "ecs/ecs.h"
#include "game/entities/gameEntity.h"
#include "ecs/components/position.h"
#include "ecs/components/animator.h"
#include "ecs/components/sprite.h"
#include "ecs/components/gameEntityPhysics.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Player : public GameEntity
{
private:
	class PlayerTag
	{
	private:
		std::shared_ptr<PositionComponent> posComp;
		std::shared_ptr<SpriteComponent> sprComp;
		std::shared_ptr<Entity> tagEntity;
	public:
		PlayerTag(const std::string &tagTexture);

		void SetPlayerPosition(Vector2 playerPosition);
	};

private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<AnimatorComponent> animComp = std::make_shared<AnimatorComponent>();
	std::shared_ptr<GameEntityPhysicsComponent> physComp = std::make_shared<GameEntityPhysicsComponent>();
	std::shared_ptr<Entity> body = std::make_shared<Entity>();

	UCHAR leftKey;
	UCHAR rightKey;
	UCHAR jetpackKey;
	UCHAR powerKey;

	Texture *leftOffSpritesheetTexture;
	Texture *leftOnSpritesheetTexture;
	Texture *rightOffSpritesheetTexture;
	Texture *rightOnSpritesheetTexture;

	PlayerTag tag;
public:
	Player(std::string color, bool isPlayer1, Vector2 spawnPt);
	void SetLeftKey(UCHAR leftKey) { this->leftKey = leftKey; }
	void SetRightKey(UCHAR rightKey) { this->rightKey = rightKey; }
	void SetJetpackKey(UCHAR jetpackKey) { this->jetpackKey = jetpackKey; }
	void SetPowerKey(UCHAR powerKey) { this->powerKey = powerKey; }
	void SetVelocity(float speed) { physComp->velocity.x = speed; physComp->velocity.y = -speed; }
	void SetX(float newX) { posComp->pos.x = newX; }
	void SetY(float newY) { posComp->pos.y = newY; }
	void Update(float deltaTime) override;
};