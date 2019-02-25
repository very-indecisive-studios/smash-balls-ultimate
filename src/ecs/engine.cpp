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

std::shared_ptr<EntityList> ECSEngine::GetEntities(const std::string &listTag)
{
	auto matchedEntities = std::make_shared<EntityList>();

	for (auto &entity: entities)
	{
		if (entity->GetListTag() == listTag)
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

void ECSEngine::RemoveEntity(std::shared_ptr<Entity> entity)
{
	int foundIndex = -1;
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i] == entity)
		{
			foundIndex = i;
			break;
		}
	}

	if (foundIndex >= 0)
	{
		entities.erase(entities.begin() + foundIndex);
	}
}