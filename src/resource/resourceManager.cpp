#include "pch.h"

#include "resourceManager.h"
#include "context/context.h"

ResourceManager::ResourceManager() { }

ResourceManager::~ResourceManager() 
{
	// Deallocate all textures.
	for (const auto& pair : textureResourceMap) 
	{
		delete pair.second;
	}

	// Deallocate all fonts.
	for (const auto& font : fontResourceList)
	{
		delete font;
	}

	// Deallocate all persistent audio.
	for (const auto& pair : persistentAudioPlayerMap)
	{
		delete pair.second;
	}
}

Texture * ResourceManager::GetTexture(const std::string &textureName)
{
	auto itr = textureResourceMap.find(textureName);

	if (itr != textureResourceMap.end())
	{
		return itr->second;
	}

	Texture *loadedTexture = Context::GraphicsRenderer()->LoadTextureFromFile(textureName);

	textureResourceMap[textureName] = loadedTexture;

	return loadedTexture;
}


Font * ResourceManager::GetFont(const std::string& fontName, FontConfig config)
{
	for (const auto font : fontResourceList)
	{
		if (font->GetFontConfig() == config)
		{
			return font;
		}
	}
		 
	Font *loadedFont = Context::GraphicsRenderer()->LoadFont(fontName, config);

	fontResourceList.push_back(loadedFont);

	return loadedFont;
}

AudioPlayer * ResourceManager::GetPersistentAudioPlayer(const std::string& tag)
{
	auto itr = persistentAudioPlayerMap.find(tag);

	if (itr != persistentAudioPlayerMap.end())
	{
		return itr->second;
	}

	return nullptr;
}

void ResourceManager::StorePersistentAudioPlayer(AudioPlayer* pAudioPlayer, const std::string& tag)
{
	persistentAudioPlayerMap[tag] = pAudioPlayer;
}
