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

std::shared_ptr<EntityList> ECSEngine::GetEntities(ComponentBitset attachedBitset)
{
	auto matchedEntities = std::make_shared<EntityList>();

	for (auto &entity : entities)
	{
		if ((entity->GetComponentBitset() & attachedBitset) == attachedBitset)
		{
			matchedEntities->push_back(entity);
		}
	}

	return matchedEntities;
}

std::shared_ptr<EntityList> ECSEngine::GetEntities(ComponentBitset attachedBitset, ComponentBitset notAttachedBitset)
{
	auto matchedEntities = std::make_shared<EntityList>();

	for (auto &entity : entities)
	{
		if 
		(
			(entity->GetComponentBitset() & attachedBitset) == attachedBitset && 
			(entity->GetComponentBitset() & notAttachedBitset) != notAttachedBitset
		)
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
