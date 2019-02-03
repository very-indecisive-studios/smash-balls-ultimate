#include "pch.h"

#include "gameScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

GameScene::GameScene(std::string p1Color, std::string p2Color, std::string gameMode)
	: p1Color(p1Color), p2Color(p2Color), gameMode(gameMode)
{ }

GameScene::~GameScene()
{ }

void GameScene::Initialize()
{
	background = std::make_unique<Background>(Resources::GAME_SCENE_IMAGE);

	ball = std::make_unique<Ball>(Resources::BALL_RADIUS);

	//floor = std::make_unique<Wall>(0, Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT, Resources::GROUND_HEIGHT, Constants::GAME_WIDTH);
	ceiling = std::make_unique<Wall>(0, 0, 0, Constants::GAME_WIDTH);
	leftWall = std::make_unique<Wall>(0, 0, Constants::GAME_HEIGHT, 0);
	rightWall = std::make_unique<Wall>(Constants::GAME_WIDTH, 0, Constants::GAME_HEIGHT, 0);

	leftGoalpostCeiling = std::make_unique<Wall>(Resources::LEFT_GOALPOST_X, Resources::LEFT_GOALPOST_Y, 5, Resources::GOALPOST_WIDTH);
	rightGoalpostCeiling = std::make_unique<Wall>(Resources::RIGHT_GOALPOST_X, Resources::RIGHT_GOALPOST_Y, 5, Resources::GOALPOST_WIDTH);
	leftGoalpost = std::make_unique<Goalpost>(Resources::LEFT_GOALPOST_IMAGE, Resources::LEFT_GOALPOST_X, Resources::LEFT_GOALPOST_Y);
	rightGoalpost = std::make_unique<Goalpost>(Resources::RIGHT_GOALPOST_IMAGE, Resources::RIGHT_GOALPOST_X, Resources::RIGHT_GOALPOST_Y);

	scoreboard = std::make_unique<Scoreboard>(p1Color, p2Color);
	timer = std::make_unique<Timer>();

	pauseText = std::make_unique<TextObject>(
		Resources::FONT_TYPE,
		Vector2(0, Constants::GAME_HEIGHT / 2 - (Resources::FONT_SIZE * 3 / 2)),
		"",
		Constants::GAME_HEIGHT,
		Constants::GAME_WIDTH,
		TextAlignPosition::H_CENTER,
		Resources::FONT_SIZE * 3,
		Resources::FONT_COLOR_BLACK,
		false,
		[this]() { }
	);

	
	player1 = std::make_unique<Player>(p1Color, true, Vector2(Resources::P1_SPAWNX, Resources::P1_SPAWNY));

	player1->SetLeftKey(Resources::P1_LEFT_KEY);
	player1->SetRightKey(Resources::P1_RIGHT_KEY);
	player1->SetJetpackKey(Resources::P1_JETPACK_KEY);
	player1->SetPowerKey(Resources::P1_POWER_KEY);
	player1->SetVelocity(Resources::P1_SPEED);

	player2 = std::make_unique<Player>(p2Color, false, Vector2(Resources::P2_SPAWNX, Resources::P2_SPAWNY));
	player2->SetLeftKey(Resources::P2_LEFT_KEY);
	player2->SetRightKey(Resources::P2_RIGHT_KEY);
	player2->SetJetpackKey(Resources::P2_JETPACK_KEY);
	player2->SetPowerKey(Resources::P2_POWER_KEY);
	player2->SetVelocity(Resources::P2_SPEED);
}

void GameScene::Update(float deltaTime)
{
	if (Context::InputManager()->IsKeyDown(VK_ESCAPE))
	{
		Context::InputManager()->ClearAll();
		isPaused = !isPaused;
	}
	if (isPaused)
	{
		pauseText->SetText("PAUSED");
		return;
	}
	else 
	{
		pauseText->SetText("");
	}

	ball->Update(deltaTime);
	player1->Update(deltaTime);
	player2->Update(deltaTime);
}