#include "../include/StartScreen.h"

enum buttonList {
	PLAY = 0,
	OPTION = 1,
	EXIT = 2,
	CREDIT = 3
};

StartScreen::StartScreen() {
	button[PLAY] = Texture::loadTexture("assets/PLAY.png");
	button[OPTION] = Texture::loadTexture("assets/PLAY.png");
	button[EXIT] = Texture::loadTexture("assets/PLAY.png");
	button[CREDIT] = Texture::loadTexture("assets/PLAY.png");
}

StartScreen::~StartScreen() {

}

void StartScreen::update() {

}

void StartScreen::render() {

}