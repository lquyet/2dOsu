#include "../include/OptionMenu.h"

OptionMenu::OptionMenu() {
	SDL_Color color = { 0,0,0 };
	TTF_Font* font = TTF_OpenFont("font/Bariol.ttf", 50);
	//SDL_SetRenderDrawColor(Game::renderer, 52, 235, 229, 200); //200 alpha
	guideText = new Textbox("Choose your character", font, color, 20, 20);
	backToMenu = new Button("assets/button_back.png", 0, 700);
	backToMenu->bFocus = Texture::loadTexture("assets/button_back_focus.png");
	backToMenu->center(1000);
	character[HARRY] = new Button("assets/harry.png", 0, 100);
	character[VOLDEMORT] = new Button("assets/voldemort.png", 0, 250);
	character[DUMBLEDORE] = new Button("assets/dumbledore.png", 0, 400);
	for (int i = 0; i < 3; i++) {
		character[i]->scale(0.5);
		character[i]->center(WIDTH / 2);
	}
	// character 0 -> 2
	TTF_CloseFont(font);
}

OptionMenu::~OptionMenu() {
	guideText->~Textbox();
	guideText = NULL;
	for (int i = 0; i < 3; i++) {
		character[i]->~Button();
		character[i] = NULL;
	}
	backToMenu->~Button();
	backToMenu = NULL;
}

void OptionMenu::render() {
	guideText->render();
	for (int i = 0; i < 3; i++) {
		character[i]->render();
	}
	backToMenu->render();
}

void OptionMenu::update() {
	for (int i = 0; i < 3; i++) {
		character[i]->update();
	}
	backToMenu->update();
}