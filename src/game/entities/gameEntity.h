#pragma once

class GameEntity
{
protected:
	GameEntity() { }

public:
	virtual ~GameEntity() { }

	virtual void Update(float deltaTime) = 0;
};