#pragma once

#include <cstdint>
#include "raylib.h"
#include "Window.h"

class Player
{
public:
	Player();
	Rectangle Rec;
	uint64_t Score;
	uint8_t Lives;
};

