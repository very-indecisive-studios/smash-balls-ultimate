#include "pch.h"

#include "context.h"
#include "game/gameException.h"

Context::Context()
{
	graphicsRenderer	= new ::GraphicsRenderer();
	resourceManager		= new ::ResourceManager();
	inputManager		= new ::InputManager();
	audioEngine			= new ::AudioEngine();
	ecsEngine			= new ::ECSEngine();
	sceneManager		= new ::SceneManager();
	game				= new ::Game();
}

Context::~Context()
{
	// Delete in this order.
	delete game;
	delete sceneManager;
	delete ecsEngine;
	delete resourceManager;
	delete audioEngine;
	delete graphicsRenderer;
	delete inputManager;
}

GraphicsRenderer * Context::GraphicsRenderer()
{
	return instance->graphicsRenderer;
}

ResourceManager * Context::ResourceManager()
{
	return instance->resourceManager;
}

InputManager * Context::InputManager()
{
	return instance->inputManager;
}

AudioEngine	 * Context::AudioEngine()
{
	return instance->audioEngine;
}

SceneManager * Context::SceneManager()
{
	return instance->sceneManager;
}

Game * Context::Game()
{
	return instance->game;
}

ECSEngine * Context::ECSEngine()
{
	return instance->ecsEngine;
}

/*
	Static variables.
*/

Context * Context::instance = nullptr;

void Context::ReleaseAll()
{
	delete instance;
	instance = nullptr;
}

void Context::Initialize() 
{
	if (instance == nullptr) 
	{
		instance = new Context();
	}
}

bool Context::IsInitialized()
{
	return instance != nullptr;
}
