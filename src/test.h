#pragma once

#include <iostream>
#include "ecs/ecs.h"

struct PositionComponent : public Component
{
	int x;
	int y;
};

class DummySystem2 : public System
{
private:
	std::shared_ptr<std::vector<std::shared_ptr<Entity>>> entitiesToProcess;
	
	ComponentBitset interestBitset;
	const ComponentId posComponentId = ComponentUtils::GetComponentId<PositionComponent>();
public:	
	DummySystem2()
	{
		interestBitset.set(posComponentId);
	}

	void Process(float deltaTime) override
	{
		entitiesToProcess = Context::Get()->GetECSEngine()->GetEntities(interestBitset);

		for (auto &entity : *entitiesToProcess)
		{
			auto posComponent = std::static_pointer_cast<PositionComponent>(entity->GetComponent<PositionComponent>());

			std::cout << "x: " << posComponent->x << " y: " << posComponent->y << std::endl;
		}
	}
};
