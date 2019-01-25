#include "pch.h"

#include "context.h"
#include "game/gameException.h"

Context::Context()
{
	graphicsRenderer = new GraphicsRenderer();
	resourceManager = new ResourceManager();
	inputManager = new InputManager();
	audioEngine = new AudioEngine();
	sceneManager = new SceneManager();
	game = new Game();
	ecsEngine = new ECSEngine();
}

Context::~Context()
{
	// Delete in this order.
	delete ecsEngine;

	delete sceneManager;
	delete game;

	delete resourceManager;

	delete audioEngine;
	delete graphicsRenderer;
	delete inputManager;
}

GraphicsRenderer * Context::GetGraphicsRenderer()
{
	return graphicsRenderer;
}

ResourceManager * Context::GetResourceManager()
{
	return resourceManager;
}

InputManager * Context::GetInputManager()
{
	return inputManager;
}

AudioEngine	 * Context::GetAudioEngine()
{
	return audioEngine;
}

SceneManager * Context::GetSceneManager()
{
	return sceneManager;
}

Game * Context::GetGame()
{
	return game;
}

ECSEngine * Context::GetECSEngine()
{
	return ecsEngine;
}

/*
	Static variables.
*/

Context * Context::instance = nullptr;

Context * Context::Get() 
{
	return instance;
}

void Context::Initialize() 
{
	if (instance == nullptr) 
	{
		instance = new Context();
	}
}

void Context::ReleaseAll() 
{
	delete instance;
	instance = nullptr;
}
