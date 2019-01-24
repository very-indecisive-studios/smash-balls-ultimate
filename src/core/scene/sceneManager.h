#pragma once

#include "scene.h"
#include "mainMenuScene.h"
#include "selectionScene.h"

class SceneManager
{
private:
	Scene *currentScene = nullptr;
	Scene *pendingSceneToLoad = nullptr;

public:
	SceneManager();
	~SceneManager();

	void Initialize();

	void LoadMainMenuScene();
	void LoadSelectionScene();

	void Update(float deltaTime);
};
