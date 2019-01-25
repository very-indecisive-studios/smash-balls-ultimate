#pragma once

#include <vector>
#include <map>
#include <memory>
#include "ecs.h"

class ECSEngine
{
private:
	std::vector<std::shared_ptr<System>> systems;
	std::vector<std::shared_ptr<Entity>> entities;
public:
	void AttachSystem(std::shared_ptr<System> system);
	
	void AttachEntity(std::shared_ptr<Entity> entity);

	void ClearEntities();

	std::shared_ptr<EntityList> GetEntities(ComponentBitset attachedBitset);

	std::shared_ptr<EntityList> GetEntities(ComponentBitset attachedBitset, ComponentBitset notAttachedBitset);

	std::shared_ptr<Entity> GetTaggedEntity(const std::string &tag);

	void Update(float deltaTime);
};