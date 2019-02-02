#pragma once
#include "ecs/ecs.h"
#include "game/entities/sceneObject.h"
#include "sprites/animatedSprite.h"
#include "game/components/position.h"
#include "game/components/physics.h"
#include <memory>
#include "math/math.h"
#include "game/resources.h"

class Wall : public SceneObject
{
private:
	std::shared_ptr<PositionComponent> posComp = std::make_shared<PositionComponent>();
	std::shared_ptr<PhysicsComponent> phyComp = std::make_shared<PhysicsComponent>();
	std::shared_ptr<Entity> wall = std::make_shared<Entity>();

public:
	Wall(float x, float y, float height, float width);
	void Update(float deltaTime) override;
};