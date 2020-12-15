#include "Ball.h"

Ball::Ball()
{
	Position = { Window::Width / 2, Window::Height / 2 };
	Speed = { 600, -600 };
	Radius = 5;
}

void Ball::ResetSpeed()
{
	Speed = { 600, -600 };
}
