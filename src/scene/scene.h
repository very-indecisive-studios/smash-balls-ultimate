#pragma once

class Scene
{
public:
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
};
