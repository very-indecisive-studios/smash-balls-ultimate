#include "pch.h"

#include "engine.h"

void ECSEngine::AttachSystem(std::shared_ptr<System> system)
{
	systems.push_back(system);
}

void ECSEngine::AttachEntity(std::shared_ptr<Entity> entity)
{
	entities.push_back(entity);
}

void ECSEngine::ClearEntities()
{
	entities.clear();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> ECSEngine::GetEntities(ComponentBitset bitset)
{
	auto matchedEntities = std::make_shared<std::vector<std::shared_ptr<Entity>>>();

	for (auto &entity : entities)
	{
		if ((entity->GetComponentBitset() & bitset) == bitset)
		{
			matchedEntities->push_back(entity);
		}
	}

	return matchedEntities;
}

std::shared_ptr<Entity> ECSEngine::GetTaggedEntity(const std::string & tag)
{
	for (auto &entity : entities)
	{
		if (entity->GetTag() == tag)
		{
			return entity;
		}
	}

	return nullptr;
}

void ECSEngine::Update(float deltaTime)
{
	for (auto &system : systems)
	{
		system->Process(deltaTime);
	}
}
