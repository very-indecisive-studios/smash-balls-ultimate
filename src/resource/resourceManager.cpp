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

	persistentAudioPlayerMap.clear();
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

std::shared_ptr<AudioPlayer> ResourceManager::CreateAudioPlayer(const std::wstring& audioFileName)
{
	std::shared_ptr<AudioPlayer> audioPlayer(Context::AudioEngine()->CreateAudioPlayer(audioFileName));
	
	return audioPlayer;
}


std::shared_ptr<AudioPlayer> ResourceManager::CreatePersistentAudioPlayer(const std::wstring& audioFileName, const std::string& tag)
{
	auto itr = persistentAudioPlayerMap.find(tag);

	if (itr != persistentAudioPlayerMap.end())
	{
		return itr->second;
	}

	std::shared_ptr<AudioPlayer> audioPlayer(Context::AudioEngine()->CreateAudioPlayer(audioFileName));

	persistentAudioPlayerMap[tag] = audioPlayer;

	return audioPlayer;
}

std::shared_ptr<AudioPlayer> ResourceManager::GetPersistentAudioPlayer(const std::string& tag)
{
	auto itr = persistentAudioPlayerMap.find(tag);

	if (itr != persistentAudioPlayerMap.end())
	{
		return itr->second;
	}

	return nullptr;
}
