#pragma once
#include "Textbox.h"

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