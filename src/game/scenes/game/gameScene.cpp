#include "pch.h"

#include "gameScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"
#include "game/scenes/selection/selectionScene.h"
#include "game/scenes/gameOver/gameOverScene.h"
#include "ecs/systems/physics/physics.h"

GameScene::GameScene(std::string p1Color, std::string p2Color, GameMode gm)
	: p1Color(p1Color), p2Color(p2Color)
{ 
	if (gm.isTimed)
	{
		timeLimit = gm.limit;
	}
	else
	{
		goalLimit = gm.limit;
	}
}

GameScene::~GameScene()
{ }

void GameScene::Initialize()
{
	Context::ECSEngine()->GetSystem<PhysicsSystem>()->SetIsActive(true);

	background = std::make_unique<Background>(Resources::GAME_SCENE_IMAGE);

	ball = std::make_unique<Ball>(Resources::BALL_RADIUS);

	floor = std::make_unique<Wall>(-10, Constants::GAME_HEIGHT - Resources::GROUND_HEIGHT, Resources::GROUND_HEIGHT, Constants::GAME_WIDTH);
	ceiling = std::make_unique<Wall>(-10, 0, 0, Constants::GAME_WIDTH + 100);
	leftWall = std::make_unique<Wall>(0, 0, Constants::GAME_HEIGHT, 10);
	rightWall = std::make_unique<Wall>(Constants::GAME_WIDTH, 0, Constants::GAME_HEIGHT, 10);

	leftGoalpostCeiling = std::make_unique<Wall>(Resources::LEFT_GOALPOST_X, Resources::LEFT_GOALPOST_Y, 5, Resources::GOALPOST_WIDTH);
	rightGoalpostCeiling = std::make_unique<Wall>(Resources::RIGHT_GOALPOST_X, Resources::RIGHT_GOALPOST_Y, 5, Resources::GOALPOST_WIDTH);
	leftGoalpost = std::make_unique<Goalpost>(Resources::LEFT_GOALPOST_IMAGE, Resources::LEFT_GOALPOST_X, Resources::LEFT_GOALPOST_Y);
	rightGoalpost = std::make_unique<Goalpost>(Resources::RIGHT_GOALPOST_IMAGE, Resources::RIGHT_GOALPOST_X, Resources::RIGHT_GOALPOST_Y);

	scoreboard = std::make_unique<Scoreboard>(p1Color, p2Color);
	timer = std::make_unique<Timer>();

	middleText = std::make_unique<TextObject>(
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

	instructionText = std::make_unique<TextObject>(
		Resources::FONT_TYPE,
		Vector2(0, Constants::GAME_HEIGHT / 2 + (Resources::FONT_SIZE)),
		"",
		Constants::GAME_HEIGHT,
		Constants::GAME_WIDTH,
		TextAlignPosition::H_CENTER,
		Resources::FONT_SIZE,
		Resources::FONT_COLOR_BLACK,
		false,
		[this]() {}
	);
	
	player1 = std::make_unique<Player>(p1Color, true, Vector2(Resources::P1_SPAWNX, Resources::P1_SPAWNY));

	player1->SetLeftKey(Resources::P1_LEFT_KEY);
	player1->SetRightKey(Resources::P1_RIGHT_KEY);
	player1->SetJetpackKey(Resources::P1_JETPACK_KEY);
	player1->SetPowerKey(Resources::P1_POWER_KEY);

	player2 = std::make_unique<Player>(p2Color, false, Vector2(Resources::P2_SPAWNX, Resources::P2_SPAWNY));
	player2->SetLeftKey(Resources::P2_LEFT_KEY);
	player2->SetRightKey(Resources::P2_RIGHT_KEY);
	player2->SetJetpackKey(Resources::P2_JETPACK_KEY);
	player2->SetPowerKey(Resources::P2_POWER_KEY);

	Context::ResourceManager()->GetPersistentAudioPlayer(Resources::BG_MUSIC_AUDIO_TAG)->Stop();

	crowdBgAudioPlayer = Context::ResourceManager()->CreateAudioPlayer(Resources::CROWD_BG_AUDIO);
	crowdBgAudioPlayer->SetVolume(0.5f);
	crowdBgAudioPlayer->SetLooping(true);
	crowdBgAudioPlayer->Play();

	crowdCheerAudioPlayer = Context::ResourceManager()->CreateAudioPlayer(Resources::CROWD_CHEER_AUDIO);
	whistleAudioPlayer = Context::ResourceManager()->CreateAudioPlayer(Resources::WHISTLE_AUDIO);
	goalNetAudioPlayer = Context::ResourceManager()->CreateAudioPlayer(Resources::GOALPOST_NET_AUDIO);

	whistleAudioPlayer->Play();
}

bool GameScene::P1Score() 
{
	Vector2 ballPos = ball->GetPos();
	Vector2 oppGoalLine = rightGoalpost->GetGoalLine(false); // right goalpost

	if (ballPos.x >= oppGoalLine.x && ballPos.y > oppGoalLine.y)
	{
		return true;
	}
	
	return false;
}

bool GameScene::P2Score()
{
	Vector2 ballPos = ball->GetPos();
	Vector2 oppGoalLine = leftGoalpost->GetGoalLine(true); // left goalpost

	if (ballPos.x <= oppGoalLine.x - Resources::BALL_RADIUS * 2 && ballPos.y > oppGoalLine.y)
	{
		return true;
	}

	return false;
}

void GameScene::ResetRound() 
{

	// reset ball
	ball->Reset();

	// reset players
	player1->SetX(Resources::P1_SPAWNX);
	player1->SetY(Resources::P1_SPAWNY);
	player2->SetX(Resources::P2_SPAWNX);
	player2->SetY(Resources::P2_SPAWNY);

	// remove text
	middleText->SetText("");
}

void GameScene::CheckGameOver()
{
	if (goalLimit != 0) // goal based
	{
		if (p1Score == goalLimit) 
		{
			whistleAudioPlayer->Play();
			crowdCheerAudioPlayer->Play();

			Context::SceneManager()->LoadScene<GameOverScene>(1);
		}

		if (p2Score == goalLimit)
		{
			whistleAudioPlayer->Play();
			crowdCheerAudioPlayer->Play();

			Context::SceneManager()->LoadScene<GameOverScene>(2);
		}
	}
	else // time based
	{
		if (timeLimit - totalTime <= 0)
		{
			whistleAudioPlayer->Play();
			crowdCheerAudioPlayer->Play();

			if (p1Score > p2Score)
			{
				Context::SceneManager()->LoadScene<GameOverScene>(1);
			}
			else if (p2Score > p1Score)
			{
				Context::SceneManager()->LoadScene<GameOverScene>(2);
			}
			else if (p1Score == p2Score)
			{
				Context::SceneManager()->LoadScene<GameOverScene>(0);
			}
		}
	}
}

void GameScene::Pause(float deltaTime)
{
	if (Context::InputManager()->IsKeyDown(VK_ESCAPE))
	{
		Context::InputManager()->ClearAll();
		isPaused = !isPaused;

		if (!isPaused) 
		{
			Context::ECSEngine()->GetSystem<PhysicsSystem>()->SetIsActive(true); // Reactivate physics system
			instructionText->SetText("");
			middleText->SetText("");
		}
	}

	if (isPaused)
	{
		totalTime -= deltaTime; // Stop time

		Context::ECSEngine()->GetSystem<PhysicsSystem>()->SetIsActive(false); // Deactivate physics system
		
		middleText->SetText("PAUSED");
		instructionText->SetText("Esc - Resume | R - Restart");

		// Restart game
		if (Context::InputManager()->IsKeyDown(0x52))
		{
			Context::InputManager()->ClearAll();
			Context::SceneManager()->LoadScene<SelectionScene>();
		}

		return;
	}
}

void GameScene::Update(float deltaTime)
{
	totalTime += deltaTime;
	
	Pause(deltaTime);

	// Set timer
	if (timeLimit != 0)
	{
		timer->SetSeconds(timeLimit - totalTime);
	}
	else 
	{
		timer->SetSeconds(totalTime);
	}

	// Check if player 1 scored
	if (P1Score() && !toReset)
	{
		goalNetAudioPlayer->Play();
		crowdCheerAudioPlayer->Play();

		currentTime = totalTime;
		p1Score++;
		scoreboard->SetLeftPlayerScore(p1Score);
		middleText->SetText("PLAYER 1 SCORES!");
		toReset = true;
	}

	// Check if player 2 scored
	if (P2Score() && !toReset)
	{
		goalNetAudioPlayer->Play();
		crowdCheerAudioPlayer->Play();

		currentTime = totalTime;
		p2Score++;
		scoreboard->SetRightPlayerScore(p2Score);
		middleText->SetText("PLAYER 2 SCORES!");
		toReset = true;
	}

	// Reset round after 3 seconds
	if (toReset && totalTime - currentTime >= 3)
	{
		whistleAudioPlayer->Play();

		ResetRound();
		toReset = false;
	}

	ball->Update(deltaTime);
	player1->Update(deltaTime);
	player2->Update(deltaTime);
	CheckGameOver();
}