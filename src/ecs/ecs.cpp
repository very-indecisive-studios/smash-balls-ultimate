#include "pch.h"

#include "ecs.h"

// Static member variables.
ComponentId ComponentUtils::idCounter = 0;
std::map<size_t, ComponentId> ComponentUtils::componentIdMap;
