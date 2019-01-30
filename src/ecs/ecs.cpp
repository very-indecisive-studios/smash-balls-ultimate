#include "pch.h"

#include "ecs.h"

// Static member variables.
ComponentId Component::idCounter = 0;
std::map<size_t, ComponentId> Component::componentIdMap;
