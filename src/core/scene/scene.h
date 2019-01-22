#pragma once

#include <vector>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Update(float deltaTime) = 0;
};
