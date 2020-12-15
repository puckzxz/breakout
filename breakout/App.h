#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Window.h"
#include "Brick.h"
#include "Ball.h"
#include "Player.h"

class App
{
public:
    App();
    void Run();
private:
    void update();
    void draw();
    void reset();
    void nextLevel();

    bool _paused = false;
    bool _dead = true;

    std::unique_ptr<Player> _player;
    std::unique_ptr<Ball> _ball;
    std::vector<Brick> _bricks;

    uint64_t _level = 1;

    const uint8_t _rowsOfBricks = 5;
    const uint8_t _bricksPerRow = 12;
    const float_t _brickWidth = static_cast<float_t>(Window::Width) / _bricksPerRow;
    const uint8_t _brickHeight = 40;
    const uint8_t _brickPadding = 2;

    const inline Color brickRowToColor(int br) const;
    const void generateBricks();
};

