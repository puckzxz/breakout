#pragma once

#include "raylib.h"
#include "Window.h"

class Ball
{
public:
	Ball();
	void ResetSpeed();
	Vector2 Position;
	Vector2 Speed;
	float Radius;
};
