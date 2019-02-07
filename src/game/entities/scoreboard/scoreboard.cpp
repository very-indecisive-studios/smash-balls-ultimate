#include "pch.h"

#include "scoreboard.h"
#include "context/context.h"
#include "game/resources.h"
#include "game/layers.h"
#include "game/data.h"

Scoreboard::Score::Score(const std::string &playerColour, bool alignLeft)
{
	/* Score entity */
	scoreEntity = std::make_shared<Entity>();

	scorePosComp = std::make_shared<PositionComponent>();
	scorePosComp->pos = alignLeft ? GameSceneData::Scoreboard::SCORE_LOCATION_LEFT : GameSceneData::Scoreboard::SCORE_LOCATION_RIGHT;
	scoreEntity->AttachComponent<PositionComponent>(scorePosComp);

	scoreTextComp = std::make_shared<TextComponent>();
	scoreTextComp->text = "0";
	scoreTextComp->width = GameSceneData::Scoreboard::SCORE_FONT_WIDTH;
	scoreTextComp->height = GameSceneData::Scoreboard::SCORE_FONT_SIZE;
	scoreTextComp->layer = Layers::UI_TEXT;
	scoreTextComp->color = alignLeft ? Resources::PLAYER_1_TAG_COLOUR : Resources::PLAYER_2_TAG_COLOUR;
	scoreTextComp->alignment = alignLeft ? TextAlignPosition::LEFT : TextAlignPosition::RIGHT;
	scoreTextComp->font = Context::ResourceManager()->GetFont(Resources::FONT_TYPE, FontConfig{ GameSceneData::Scoreboard::SCORE_FONT_SIZE });
	scoreEntity->AttachComponent<TextComponent>(scoreTextComp);

	Context::ECSEngine()->AttachEntity(scoreEntity);

	/* Badge enitity */
	badgeEntity = std::make_shared<Entity>();

	badgePosComp = std::make_shared<PositionComponent>();
	badgePosComp->pos = alignLeft ? GameSceneData::Scoreboard::BADGE_LOCATION_LEFT : GameSceneData::Scoreboard::BADGE_LOCATION_RIGHT;
	badgeEntity->AttachComponent<PositionComponent>(badgePosComp);

	badgeSprComp = std::make_shared<SpriteComponent>();
	badgeSprComp->scale = GameSceneData::Scoreboard::BADGE_SCALE;
	badgeSprComp->texture = Context::ResourceManager()->GetTexture(Resources::PLAYER_BADGE_FOLDER + playerColour + ".png");
	badgeSprComp->layer = Layers::UI_IMAGE;
	badgeEntity->AttachComponent<SpriteComponent>(badgeSprComp);

	Context::ECSEngine()->AttachEntity(badgeEntity);
}

void Scoreboard::Score::SetScore(uint8_t score)
{
	scoreTextComp->text = std::to_string(score);
}

Scoreboard::Scoreboard(const std::string & leftPlayerColour, const std::string & rightPlayerColour)
	: leftPlayerScore({ leftPlayerColour, true }), rightPlayerScore({ rightPlayerColour, false })
{ }

void Scoreboard::SetLeftPlayerScore(uint8_t score)
{
	leftPlayerScore.SetScore(score);
}

void Scoreboard::SetRightPlayerScore(uint8_t score)
{
	rightPlayerScore.SetScore(score);
}
