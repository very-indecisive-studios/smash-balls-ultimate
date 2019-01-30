#include "pch.h"

#include <iostream>
#include "sceneManager.h"
#include "context/context.h"

SceneManager::SceneManager()
{ }

SceneManager::~SceneManager()
{ 
	delete currentScene;
	delete pendingSceneToLoad;
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

		Context::ECSEngine()->ClearEntities();
		currentScene->Initialize();
	}
	else
	{
		if (currentScene != nullptr)
		{
			currentScene->Update(deltaTime);
		}
	}
}
