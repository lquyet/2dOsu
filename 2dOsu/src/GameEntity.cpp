#include "../include/GameEntity.h"

GameEntity::GameEntity(Vector2 pos) {
	ePos = pos;
	eRotation = 0.0;
	eFocus = false;
}

GameEntity::~GameEntity() {

}

void GameEntity::Pos(Vector2 pos) {
	ePos = pos;
}

void GameEntity::Rotation(float rotation) {
	eRotation = rotation;
	//normalize angle
	if (eRotation > 360.0) {
		int temp = eRotation / 360;
		eRotation -= temp * 360.0;
	}
	else if (eRotation < 0.0) {
		int temp = (eRotation / 360) - 1;
		eRotation -= 360.0 * temp;
	}
}

void GameEntity::focus(bool focus) {
	eFocus = focus;
}

void GameEntity::render() {

}

void GameEntity::update() {

}



