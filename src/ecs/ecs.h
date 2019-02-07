#pragma once

#include <bitset>
#include <map>
#include <string>
#include <memory>
#include <typeinfo>

typedef uint32_t ComponentId;
constexpr size_t MAX_COMPONENTS = sizeof(ComponentId) * 8;

typedef std::bitset<MAX_COMPONENTS> ComponentBitset;

class Component
{
private:
	static ComponentId idCounter;

	static std::map<size_t, ComponentId> componentIdMap;
public:
	template <typename T>
	static ComponentId GetComponentId()
	{
		const std::type_info &typeInfo = typeid(T);

		auto itr = componentIdMap.find(typeInfo.hash_code());

		if (itr != componentIdMap.end())
		{
			return itr->second;
		}

		const ComponentId newId = idCounter++;
		componentIdMap[typeInfo.hash_code()] = newId;

		return newId;
	}
};

class Entity final
{
private:
	ComponentBitset componentBitset;
	std::shared_ptr<Component> components[MAX_COMPONENTS];
	std::string tag;
public:
	template <typename T>
	void AttachComponent(std::shared_ptr<T> component)
    {
        const ComponentId compId = Component::GetComponentId<T>();

        componentBitset.set(compId);

        components[compId] = component;
    }
	
    template <typename T>
	void RemoveComponent()
    {
        const ComponentId compId = Component::GetComponentId<T>();

        componentBitset.reset(compId);

        components[compId] = nullptr;
    }

    template <typename T>
	const std::shared_ptr<T> GetComponent()
    {
        const ComponentId compId = Component::GetComponentId<T>();

        return std::static_pointer_cast<T>(components[compId]);
    }

	ComponentBitset GetComponentBitset()
    {
        return componentBitset;
    }

	void SetTag(const std::string &tagName)
    {
        this->tag = tagName;
    }
	
	const std::string & GetTag()
    {
        return this->tag;
    }
};

typedef std::vector<std::shared_ptr<Entity>> EntityList;

class System
{
public:
	virtual void Process(float deltaTime) = 0;
};
