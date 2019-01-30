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
	LoadScene<MainMenuScene>();
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
