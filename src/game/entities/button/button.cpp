#include "pch.h"

#include "button.h"
#include "context/context.h"
#include "game/resources.h"

Button::Button(std::string pathToTexture, Vector2 pointToDraw, int height, int width, std::function<void()> callbackClicked)
{
	button->AttachComponent<PositionComponent>(posComp);
	button->AttachComponent<SpriteComponent>(spriteComp);
	Context::ECSEngine()->AttachEntity(button);

	this->height = height;
	this->width = width;
	this->callbackClicked = callbackClicked;

	spriteComp->texture = Context::ResourceManager()->GetTexture(pathToTexture);
	spriteComp->layer = 100;
	posComp->pos = pointToDraw;

	if (!(buttonClickAudioPlayer = Context::ResourceManager()->GetPersistentAudioPlayer(Resources::BUTTON_CLICK_AUDIO_TAG)))
	{
		buttonClickAudioPlayer = Context::ResourceManager()->CreatePersistentAudioPlayer(Resources::BUTTON_CLICK_AUDIO, Resources::BUTTON_CLICK_AUDIO_TAG);
	}
}

bool Button::MouseOverButton()
{
	int left = posComp->pos.x;
	int right = posComp->pos.x + width;
	int top = posComp->pos.y;
	int bottom = posComp->pos.y + height;

	if (Context::InputManager()->GetMouseX() > left &&
		Context::InputManager()->GetMouseX() < right &&
		Context::InputManager()->GetMouseY() > top &&
		Context::InputManager()->GetMouseY() < bottom)
	{
		return true;
	}
	return false;
}

void Button::PerformMouseAction() 
{
	// process of checking for mouse click (down then up) to avoid spamming
	if (Context::InputManager()->GetMouseLButton())
	{
		mouseDown = true;
	}
	if (mouseDown && !Context::InputManager()->GetMouseLButton())
	{
		mouseClicked = true;
		mouseDown = false;
	}

	if (mouseClicked && MouseOverButton())
	{
		buttonClickAudioPlayer->Play();
		callbackClicked();
	}

	// reset click
	mouseClicked = false;
}

void Button::Update(float deltaTime)
{
	PerformMouseAction();
}