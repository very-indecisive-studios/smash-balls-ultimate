#pragma once

#include <memory>
#include "game/entities/sceneObject.h"
#include "game/components/text.h"
#include "game/components/position.h"
#include "ecs/ecs.h"

class Timer : public SceneObject
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
