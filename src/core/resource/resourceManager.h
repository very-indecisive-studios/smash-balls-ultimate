#pragma once

#include <string>
#include <map>
#include "core/graphics/texture.h"
#include "core/graphics/font.h"
#include "core/audio/audio.h"
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
	Font * GetFont(const std::string& fontName, int height, UINT weight, BOOL italic);

	AudioPlayer * GetPersistentAudioPlayer(const std::string& tag);
	void StorePersistentAudioPlayer(AudioPlayer *pAudioPlayer, const std::string& tag);
};
