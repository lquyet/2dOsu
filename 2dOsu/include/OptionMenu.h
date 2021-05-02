#pragma once
#include "Textbox.h"

enum Character {
	HARRY = 0,
	VOLDEMORT = 1,
	DUMBLEDORE = 2
};

class OptionMenu {
public:
	OptionMenu();
	~OptionMenu();
	//Button* play;
	Button* backToMenu;
	Button* character[3];
	Textbox* guideText;
	void render();
	void update();
private:
};