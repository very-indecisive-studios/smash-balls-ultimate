#pragma once

enum class SceneObjectType 
{
	PLAYER,
	BALL,
	GOALPOST,
	PICKUP
};

class SceneObject
{
private:
	SceneObjectType type;

protected:
	SceneObject(SceneObjectType type);

public:
	virtual void Update(float delatTime) = 0;
};