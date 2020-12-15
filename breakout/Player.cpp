#include "Player.h"

Player::Player()
{
	Rec = {
		Window::Width / 2,
		Window::Height - 80,
		80,
		10
	};
	Lives = 5;
	Score = 0;
}
