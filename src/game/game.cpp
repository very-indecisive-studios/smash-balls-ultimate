#include "pch.h"

#include <windows.h>
#include <Mmsystem.h>
#include <iostream>
#include <string>
#include "game.h"
#include "game/resources.h"
#include "game/scenes/mainMenu/mainMenuScene.h"
#include "scene/sceneManager.h"
#include "ecs/components/position.h"
#include "ecs/components/sprite.h"
#include "ecs/systems/rendering.h"
#include "ecs/systems/rendering.h"
#include "ecs/systems/physics/physics.h"
#include "context/context.h"

Game::Game()
{}

Game::~Game()
{}

void Game::Initialize()
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeStart);

	Context::SceneManager()->LoadScene<MainMenuScene>();

	Context::ECSEngine()->AttachSystem<RenderSystem>(std::make_shared<RenderSystem>());
	Context::ECSEngine()->AttachSystem<PhysicsSystem>(std::make_shared<PhysicsSystem>());
}

void Game::Run()
{
	/*
		Calculate delta time + limit frame rate.
	*/

	// Calculate elapsed time of last frame, save in frameTime.
	QueryPerformanceCounter(&timeEnd);
	deltaTime = (float) (timeEnd.QuadPart - timeStart.QuadPart) / (float) timerFreq.QuadPart;

	// Power saving code; if not enough time has elapsed for desired frame rate.
	if (deltaTime < MIN_FRAME_TIME)
	{
		float sleepTime = (float) ((MIN_FRAME_TIME - deltaTime) * 1000);
		timeBeginPeriod(1);         // Request 1mS resolution for windows timer
		Sleep(sleepTime);           // release cpu for sleepTime
		timeEndPeriod(1);           // End 1mS timer resolution
		return;
	}

	// If frame rate is very slow.
	if (deltaTime > MAX_FRAME_TIME)
	{
		// Limit maximum frameTime.
		deltaTime = MAX_FRAME_TIME;
	}

	timeStart = timeEnd;

	/*
		Update ECS engine.
	*/
	Context::ECSEngine()->Update(deltaTime);

	/*
		Update current scene.
	*/
	Context::SceneManager()->Update(deltaTime);

	/*
		Render game.
	*/
	auto gR = Context::GraphicsRenderer();
	gR->Render();
	gR->HandleLostDevice();
}

float Game::GetDeltaTime()
{
	return deltaTime;
}
