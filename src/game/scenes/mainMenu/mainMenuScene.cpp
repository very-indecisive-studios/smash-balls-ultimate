#include "pch.h"

#include "mainMenuScene.h"
#include "game/scenes/selection/selectionScene.h"
#include "context/context.h"
#include "constants.h"
#include "game/resources.h"

MainMenuScene::MainMenuScene()
{ }

MainMenuScene::~MainMenuScene()
{ }

void MainMenuScene::Initialize()
{
	background = std::make_unique<Background>(Resources::BACKGROUND_IMAGE_MAIN_MENU);

	playText = std::make_unique<TextObject>(
		Resources::FONT_TYPE,
		Vector2(0, (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.25f)),
		"PLAY",
		(Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.5f),
		Constants::GAME_WIDTH,
		TextAlignPosition::H_CENTER,
		Resources::FONT_SIZE,
		Resources::FONT_COLOR_BLACK,
		true,
		[this]() { this->HandleButtonHover(); }
		);

	creditsText = std::make_unique<TextObject>(
		Resources::FONT_TYPE, 
		Vector2(0, (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.25f) + (Resources::BUTTON_HEIGHT + 10)),
		"CREDITS",
		Constants::GAME_HEIGHT * 0.5f - Resources::BUTTON_HEIGHT * 0.5f + Resources::BUTTON_HEIGHT + 10,
		Constants::GAME_WIDTH,
		TextAlignPosition::H_CENTER,
		Resources::FONT_SIZE,
		Resources::FONT_COLOR_BLACK,
		true,
		[this]() { this->HandleButtonHover(); }
		);

	playButton = std::make_unique<Button>(
		Resources::BUTTON_IMAGE,
		Vector2((Constants::GAME_WIDTH * 0.5f) - (Resources::BUTTON_WIDTH * 0.5f), (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.5f)),
		Resources::BUTTON_HEIGHT,
		Resources::BUTTON_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<SelectionScene>(); }
	);

	creditsButton = std::make_unique<Button>(
		Resources::BUTTON_IMAGE,
		Vector2((Constants::GAME_WIDTH * 0.5f) - (Resources::BUTTON_WIDTH * 0.5f), (Constants::GAME_HEIGHT * 0.5f) - (Resources::BUTTON_HEIGHT * 0.5f) + Resources::BUTTON_HEIGHT + 10),
		Resources::BUTTON_HEIGHT,
		Resources::BUTTON_WIDTH,
		[this]() { Context::SceneManager()->LoadScene<SelectionScene>(); }
	);

	if (!(bgMusicAudioPlayer = Context::ResourceManager()->GetPersistentAudioPlayer(Resources::BG_MUSIC_AUDIO_TAG)))
	{
		bgMusicAudioPlayer = Context::ResourceManager()->CreatePersistentAudioPlayer(Resources::BG_MUSIC_AUDIO, Resources::BG_MUSIC_AUDIO_TAG);
		bgMusicAudioPlayer->SetLooping(true);
	}

	if (!bgMusicAudioPlayer->IsPlaying())
	{
		bgMusicAudioPlayer->Play();
	}
}

void MainMenuScene::HandleButtonHover() 
{
	if (playButton->MouseOverButton()) 
	{
		playText->ChangeColor(Resources::FONT_COLOR_RED);
	}
	else 
	{
		playText->ChangeColor(Resources::FONT_COLOR_BLACK);
	}

	if (creditsButton->MouseOverButton())
	{
		creditsText->ChangeColor(Resources::FONT_COLOR_RED);
	}
	else 
	{
		creditsText->ChangeColor(Resources::FONT_COLOR_BLACK);
	}
}

void MainMenuScene::Update(float deltaTime)
{
	playButton->Update(deltaTime);
	creditsButton->Update(deltaTime);
	playText->Update(deltaTime);
	creditsText->Update(deltaTime);
}