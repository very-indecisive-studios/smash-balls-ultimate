#include "pch.h"
#include "background.h"
#include "context/context.h"

Background::Background(std::string pathToTexture)
{
	background->AttachComponent<PositionComponent>(posComp);
	background->AttachComponent<SpriteComponent>(spriteComp);
	Context::ECSEngine()->AttachEntity(background);

	posComp->pos.x = 0;
	posComp->pos.y = 0;
	spriteComp->texture = Context::ResourceManager()->GetTexture(pathToTexture);
	spriteComp->layer = 1;
}

void Background::Update(float deltaTime)
{

}