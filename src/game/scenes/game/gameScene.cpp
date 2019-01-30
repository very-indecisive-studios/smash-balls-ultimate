#include "pch.h"

#include "gameScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"


GameScene::GameScene(std::string p1Color, std::string p2Color, int gameMode)
	: p1Color(p1Color), p2Color(p2Color), gameMode(gameMode)
{ }

GameScene::~GameScene()
{ }

void GameScene::Initialize()
{
	background = std::make_unique<Background>(Resources::BACKGROUND_IMAGE);

	pauseText = Text::Create("PAUSED", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, 64, 100, false, false);

	player1 = std::make_unique<Player>(p1Color, true);
	player1->SetX(100);
	player1->SetY(500);
	player1->SetLeftKey(0x41);
	player1->SetRightKey(0x44);
	player1->SetJetpackKey(0x57);
	player1->SetPowerKey(VK_SPACE);
	player1->SetVelocity(200);

	player2 = std::make_unique<Player>(p2Color, true);
	player2->SetX(500);
	player2->SetY(500);
	player2->SetLeftKey(VK_LEFT);
	player2->SetRightKey(VK_RIGHT);
	player2->SetJetpackKey(VK_UP);
	player2->SetPowerKey(VK_SPACE);
	player2->SetVelocity(200);
}

void GameScene::Update(float deltaTime)
{
	player1->Update(deltaTime);
	player2->Update(deltaTime);

	if (Context::InputManager()->IsKeyDown(VK_ESCAPE))
	{
		Context::InputManager()->ClearAll();
		isPaused = !isPaused;
	}
	if (isPaused)
	{
		pauseText->Draw(Vector2(0, Constants::GAME_HEIGHT / 2 - 64 / 2));
		return;
	}
}