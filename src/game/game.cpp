#include "pch.h"

#include <windows.h>
#include <Mmsystem.h>
#include <iostream>
#include <string>
#include "game.h"
#include "sprites/sprite.h"
#include "context/context.h"
#include "resource/resources.h"
#include "scene/sceneManager.h"
#include "test.h"

Game::Game()
{}

Game::~Game()
{}

void Game::Initialize()
{
	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&timeStart);

	Context::Get()->GetSceneManager()->Initialize();

	auto posComponent = std::make_shared<PositionComponent>();
	posComponent->x = 100;
	posComponent->y = 500;
	auto entity1 = std::make_shared<Entity>();
	entity1->AttachComponent<PositionComponent>(posComponent);

	auto posComponent2 = std::make_shared<PositionComponent>();
	posComponent2->x = 203;
	posComponent2->y = 211;
	auto entity2 = std::make_shared<Entity>();
	entity2->AttachComponent<PositionComponent>(posComponent2);

	Context::Get()->GetECSEngine()->AttachEntity(entity1);
	Context::Get()->GetECSEngine()->AttachEntity(entity2);

	std::shared_ptr<System> s2 = std::make_shared<DummySystem2>();
	Context::Get()->GetECSEngine()->AttachSystem(s2);
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

	Context::Get()->GetECSEngine()->Update(deltaTime);

	/*
		Update current scene.
	*/
	// Context::Get()->GetSceneManager()->Update(deltaTime);

	/*
		Render game.
	*/
	auto gR = Context::Get()->GetGraphicsRenderer();
	gR->Render();
	gR->HandleLostDevice();
}

float Game::GetDeltaTime()
{
	return deltaTime;
}
