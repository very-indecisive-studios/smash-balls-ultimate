#include "pch.h"
#include "characterList.h"
#include "context/context.h"

CharacterList::CharacterList(Vector2 pointToDraw)
{
	button->AttachComponent<PositionComponent>(posComp);
	button->AttachComponent<SpriteComponent>(spriteComp);
	Context::ECSEngine()->AttachEntity(button);

	beigeTexture = Context::ResourceManager()->GetTexture(Resources::SELECTION_SCENE_BIEGE_CHAR);
	characterListTextures.push_back(beigeTexture);
	blueTexture = Context::ResourceManager()->GetTexture(Resources::SELECTION_SCENE_BLUE_CHAR);
	characterListTextures.push_back(blueTexture);
	greenTexture = Context::ResourceManager()->GetTexture(Resources::SELECTION_SCENE_GREEN_CHAR);
	characterListTextures.push_back(greenTexture);
	pinkTexture = Context::ResourceManager()->GetTexture(Resources::SELECTION_SCENE_PINK_CHAR);
	characterListTextures.push_back(pinkTexture);
	yellowTexture = Context::ResourceManager()->GetTexture(Resources::SELECTION_SCENE_YELLOW_CHAR);
	characterListTextures.push_back(yellowTexture);

	spriteComp->texture = characterListTextures[currentCharacterIndex];
	spriteComp->layer = 100;
	posComp->pos = pointToDraw;
}

void CharacterList::Next()
{
	if (currentCharacterIndex == characterListTextures.size() - 1) 
	{
		currentCharacterIndex = 0;
	}
	else 
	{
		currentCharacterIndex++;
	}
}

void CharacterList::Previous()
{
	if (currentCharacterIndex == 0)
	{
		currentCharacterIndex = characterListTextures.size() - 1;
	}
	else
	{
		currentCharacterIndex--;
	}
}

std::string CharacterList::GetCurrentCharacterColor()
{
	if (currentCharacterIndex == 0)
	{
		return "beige";
	}
	else if (currentCharacterIndex == 1) 
	{
		return "blue";
	}
	else if (currentCharacterIndex == 2)
	{
		return "green";
	}
	else if (currentCharacterIndex == 3)
	{
		return "pink";
	}
	else if (currentCharacterIndex == 4)
	{
		return "yellow";
	}
}

void CharacterList::Update(float deltaTime)
{
	spriteComp->texture = characterListTextures[currentCharacterIndex];
}