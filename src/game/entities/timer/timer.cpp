#include "pch.h"

#include "timer.h"
#include "context/context.h"
#include "game/resources.h"
#include "game/layers.h"
#include "game/data.h"
#include "constants.h"

Timer::Timer()
{
	timerEntity = std::make_shared<Entity>();

	timerPosComp = std::make_shared<PositionComponent>();
	timerPosComp->pos = Vector2(0.0f, 0.0f);
	timerEntity->AttachComponent<PositionComponent>(timerPosComp);

	timerTextComp = std::make_shared<TextComponent>();
	timerTextComp->text = "00:00";
	timerTextComp->height = GameSceneData::Timer::TIMER_FONT_SIZE;
	timerTextComp->width = Constants::GAME_WIDTH;
	timerTextComp->layer = Layers::UI_TEXT;
	timerTextComp->color = 0xFF000000;
	timerTextComp->alignment = TextAlignPosition::H_CENTER | TextAlignPosition::V_CENTER;
	timerTextComp->font = Context::ResourceManager()->GetFont(Resources::FONT_TYPE, FontConfig { GameSceneData::Timer::TIMER_FONT_SIZE, FontWeight::LIGHT });
	timerEntity->AttachComponent<TextComponent>(timerTextComp);

	Context::ECSEngine()->AttachEntity(timerEntity);
}

void Timer::SetSeconds(float totalSeconds)
{
	int minutes = static_cast<int>(totalSeconds) / 60;
	int seconds = static_cast<int>(totalSeconds) % 60;

	std::string minutesText = minutes > 10 ? std::to_string(minutes) : "0" + std::to_string(minutes);
	std::string secondsText = seconds >= 10 ? std::to_string(seconds) : "0" + std::to_string(seconds);

	timerTextComp->text = minutesText + ":" + secondsText;
}
