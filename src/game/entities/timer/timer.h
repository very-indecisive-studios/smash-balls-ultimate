#pragma once

#include <memory>
#include "game/entities/gameEntity.h"
#include "ecs/components/text.h"
#include "ecs/components/position.h"
#include "ecs/ecs.h"

class Timer : public GameEntity
{
private:
	std::shared_ptr<TextComponent> timerTextComp;
	std::shared_ptr<PositionComponent> timerPosComp;
	std::shared_ptr<Entity> timerEntity;
public:
	Timer();

	void SetSeconds(float totalSeconds);

	void Update(float deltaTime) override { };
};
