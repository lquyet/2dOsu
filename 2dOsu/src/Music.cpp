#include "../include/Music.h"

Music::Music() {

}

Music::~Music() {
	Mix_FreeMusic(background);
	for (int i = 0; i < 16; i++) Mix_FreeChunk(chunkList[i]);
}

