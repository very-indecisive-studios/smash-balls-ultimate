#include "pch.h"

#include "gameScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"


GameScene::GameScene(int player1, int player2, int gameMode)
{
	background = Context::ResourceManager()->GetTexture(Resources::BACKGROUND_IMAGE);
	spriteComp->texture = background;
	spriteComp->layer = 100;

	pauseText = Text::Create("PAUSED", Resources::FONT_TYPE, Resources::FONT_COLOR_BLACK, 64, 100, false, false);
	p1 = new Player("blue", true);
	p1->SetX(100);
	p1->SetY(100);
	p1->SetLeftKey(0x41);
	p1->SetRightKey(0x44);
	p1->SetJetpackKey(0x57);
	p1->SetPowerKey(VK_SPACE);
	p1->SetVelocity(100);
}

GameScene::~GameScene()
{
}

void GameScene::Update(float deltaTime)
{
	p1->Update(deltaTime);

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