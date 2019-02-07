#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "sprites/animatedSprite.h"
#include "ecs/components/position.h"
#include "ecs/components/gameEntityPhysics.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Wall : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<GameEntityPhysicsComponent> phyComp = std::make_shared<GameEntityPhysicsComponent>();
	std::shared_ptr<Entity> wall = std::make_shared<Entity>();

public:
	Wall(float x, float y, float height, float width);
	void Update(float deltaTime) override;
};