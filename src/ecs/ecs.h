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
	Component() { };
	virtual ~Component() { }

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
	std::string listTag;
public:
	Entity() { }
	~Entity() { }

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
	
	void SetListTag(const std::string &listTag)
	{
		this->listTag = listTag;
	}

	const std::string & GetTag()
    {
        return this->tag;
    }

	const std::string & GetListTag()
	{
		return this->listTag;
	}
};

typedef std::vector<std::shared_ptr<Entity>> EntityList;

class System
{
private:
	bool isActive = true;
public:
	System() { }
	virtual ~System() { }

	void SetIsActive(bool active) { this->isActive = active;  }
	bool GetIsActive() { return this->isActive; };

	virtual void Process(float deltaTime) = 0;
};
