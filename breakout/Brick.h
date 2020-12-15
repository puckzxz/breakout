#pragma once

#include <cstdint>
#include "raylib.h"

class Brick
{
public:
	Rectangle Rec;
	uint8_t Score;
	bool Active;
	Color Color;
	uint16_t Speed;
};
