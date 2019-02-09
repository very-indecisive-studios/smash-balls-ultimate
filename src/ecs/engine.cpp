#include "pch.h"

#include "engine.h"

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
	for (auto &system : systemsMap)
	{
		if (system.second->GetIsActive())
		{
			system.second->Process(deltaTime);
		}
	}
}
