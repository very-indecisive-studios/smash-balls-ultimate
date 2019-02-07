#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include "ecs/components/gameEntityPhysics.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Goalpost : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<SpriteComponent> spriteComp = std::make_shared<SpriteComponent>();
	std::shared_ptr<GameEntityPhysicsComponent> phyComp = std::make_shared<GameEntityPhysicsComponent>();
	std::shared_ptr<Entity> goalpost = std::make_shared<Entity>();

	int height = Resources::GOALPOST_HEIGHT;
	int width = Resources::GOALPOST_WIDTH;

public:
	Goalpost(std::string pathToImage, float x, float y);
	Vector2 GetGoalLine(bool isLeft);
	void Update(float deltaTime) override;
};