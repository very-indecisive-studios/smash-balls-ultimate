#pragma once

#include <string>
#include <map>
#include "graphics/texture.h"
#include "graphics/font.h"
#include "audio/audio.h"
#include <vector>

class ResourceManager 
{
private:
	std::map<std::string, Texture *> textureResourceMap;
	std::map<std::string, AudioPlayer *> persistentAudioPlayerMap;
	std::vector<Font *> fontResourceList;
public:
	ResourceManager();
	~ResourceManager();

	Texture * GetTexture(const std::string &textureName);
	Font * GetFont(const std::string& fontName, FontConfig config);

	AudioPlayer * GetPersistentAudioPlayer(const std::string& tag);
	void StorePersistentAudioPlayer(AudioPlayer *pAudioPlayer, const std::string& tag);
};
