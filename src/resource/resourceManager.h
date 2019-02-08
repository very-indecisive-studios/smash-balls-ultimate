#pragma once

#include <string>
#include <map>
#include <memory>
#include "graphics/texture.h"
#include "graphics/font.h"
#include "audio/audio.h"
#include <vector>

class ResourceManager 
{
private:
	std::map<std::string, Texture *> textureResourceMap;
	std::map<std::string, std::shared_ptr<AudioPlayer>> persistentAudioPlayerMap;
	std::vector<Font *> fontResourceList;
public:
	ResourceManager();
	~ResourceManager();

	Texture * GetTexture(const std::string &textureName);
	Font * GetFont(const std::string& fontName, FontConfig config);

	std::shared_ptr<AudioPlayer> CreateAudioPlayer(const std::wstring& audioName);
	std::shared_ptr<AudioPlayer> CreatePersistentAudioPlayer(const std::wstring& audioName, const std::string& tag);
	std::shared_ptr<AudioPlayer> GetPersistentAudioPlayer(const std::string& tag);
};
