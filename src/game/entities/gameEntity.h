#pragma once

class GameEntity
{
public:
	GameEntity() { }
	virtual ~GameEntity() { }
	virtual void Update(float deltaTime) = 0;
};