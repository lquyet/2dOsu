#pragma once
#include <SDL_mixer.h>
#include <string>
class Music {
public:
	Music();
	~Music();
	Mix_Music* background;
	Mix_Chunk* chunkList[16];

};