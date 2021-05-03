#pragma once
#include "Textbox.h"

enum Character {
	HARRY = 0,
	VOLDEMORT = 1,
	DUMBLEDORE = 2,
	DEFAULT = 3
};

class OptionMenu {
public:
	OptionMenu();
	~OptionMenu();
	//Button* play;
	Button* backToMenu;
	Button* character[3];
	Textbox* guideText;
	std::string characterTxPath[3] = { "assets/harry_cursor.png", "assets/voldemort_cursor.png", "assets/dumbledore_cursor.png" };
	void render();
	void update();
private:
};