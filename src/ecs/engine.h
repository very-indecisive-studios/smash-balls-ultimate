#pragma once

#include <vector>
#include <map>
#include <memory>
#include "ecs.h"

class ECSEngine final
{
private:
	std::map<std::size_t, std::shared_ptr<System>> systemsMap;
	std::vector<std::shared_ptr<Entity>> entities;
public:
	template <typename T>
	void AttachSystem(std::shared_ptr<T> system)
	{
		const std::type_info &typeInfo = typeid(T);

		systemsMap[typeInfo.hash_code()] = std::static_pointer_cast<T>(system);
	}

	template <typename T>
	std::shared_ptr<T> GetSystem()
	{
		const std::type_info &typeInfo = typeid(T);

		auto itr = systemsMap.find(typeInfo.hash_code());

		if (itr != systemsMap.end())
		{
			return std::static_pointer_cast<T>(itr->second);
		}

		return nullptr;
	}
	
	void AttachEntity(std::shared_ptr<Entity> entity);

	void ClearEntities();

	std::shared_ptr<EntityList> GetEntities(ComponentBitset attachedBitset);

	std::shared_ptr<EntityList> GetEntities(ComponentBitset attachedBitset, ComponentBitset notAttachedBitset);

	std::shared_ptr<Entity> GetTaggedEntity(const std::string &tag);

	void Update(float deltaTime);
};
