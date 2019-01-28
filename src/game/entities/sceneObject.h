#pragma once

class SceneObject
{
protected:
	SceneObject() { }

public:
	virtual ~SceneObject() { }

	virtual void Update(float deltaTime) = 0;
};