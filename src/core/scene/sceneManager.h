#pragma once

#include "scene.h"

class SceneManager
{
private:
	Scene *currentScene = nullptr;
	Scene *pendingSceneToLoad = nullptr;

public:
	SceneManager();
	~SceneManager();

	void Initialize();

	void Update(float deltaTime);
};
