#pragma once

#include "scene.h"
#include "mainMenuScene.h"
#include "selectionScene.h"
#include "gameScene.h"

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
	void LoadGameScene(int player1, int player2, int gameMode);

	void Update(float deltaTime);
};
