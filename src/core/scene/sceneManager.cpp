#include "pch.h"

#include <iostream>
#include "sceneManager.h"

SceneManager::SceneManager()
{ }

SceneManager::~SceneManager()
{ 
	delete currentScene;
}

void SceneManager::Initialize()
{
	Scene *mainMenuScene = new MainMenuScene();

	currentScene = mainMenuScene;
}

void SceneManager::LoadMainMenuScene()
{
	Scene *mainMenuScene = new MainMenuScene();

	pendingSceneToLoad = mainMenuScene;
}

void SceneManager::LoadSelectionScene()
{
	Scene *selectionScene = new SelectionScene();

	pendingSceneToLoad = selectionScene;
}

void SceneManager::Update(float deltaTime) 
{
	if (pendingSceneToLoad != nullptr)
	{
		delete currentScene;

		currentScene = pendingSceneToLoad;
		
		pendingSceneToLoad = nullptr;
	}
	else
	{
		currentScene->Update(deltaTime);
	}
}