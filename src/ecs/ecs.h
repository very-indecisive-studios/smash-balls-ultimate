#pragma once

#include <bitset>
#include <map>
#include <string>
#include <memory>
#include <typeinfo>

typedef uint32_t ComponentId;
constexpr size_t MAX_COMPONENTS = sizeof(ComponentId) * 8;

typedef std::bitset<MAX_COMPONENTS> ComponentBitset;

class ComponentUtils
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

// Forward declaration.
class Entity;

struct Component
{
	const Entity *attachedEntity;
};

typedef std::vector<std::shared_ptr<Entity>> EntityList;

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
        const ComponentId compId = ComponentUtils::GetComponentId<T>();

        componentBitset.set(compId);

        components[compId] = component;

        component->attachedEntity = this;
    }
	
    template <typename T>
	void RemoveComponent()
    {
        const ComponentId compId = ComponentUtils::GetComponentId<T>();

        componentBitset.reset(compId);

        components[compId]->attachedEntity = nullptr;

        components[compId] = nullptr;
    }

    template <typename T>
	const std::shared_ptr<T> GetComponent()
    {
        const ComponentId compId = ComponentUtils::GetComponentId<T>();

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

class System
{
public:
	virtual void Process(float deltaTime) = 0;
};
