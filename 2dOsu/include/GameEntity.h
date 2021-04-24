#pragma once
#include "Math.h"


class GameEntity {
public:
	GameEntity(Vector2 pos = VEC2_ZERO);
	~GameEntity();
	void Pos(Vector2 pos);
	void Rotation(float rotation);
	void focus(bool focus); 
	virtual void update();
	virtual void render();
private:
	Vector2 ePos;
	float eRotation;
	bool eFocus;
};