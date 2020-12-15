#include "App.h"

App::App()
{
    InitWindow(Window::Width, Window::Height, Window::Title.c_str());
    HideCursor();
    SetTargetFPS(240);
    _player = std::make_unique<Player>();
    _ball = std::make_unique<Ball>();
}

void App::Run()
{
    generateBricks();
    while (!WindowShouldClose())
    {
        update();
        draw();
    }
    CloseWindow();
}

void App::update()
{
    if (IsKeyPressed(KEY_P))
    {
        _paused = !_paused;
    }

    if (!_paused)
    {
        if (!_dead)
        {
            _ball->Position.x += (_ball->Speed.x * GetFrameTime());
            _ball->Position.y += (_ball->Speed.y * GetFrameTime());
            if ((_ball->Position.x + _ball->Radius) >= Window::Width || (_ball->Position.x - _ball->Radius) <= 0)
            {
                _ball->Speed.x *= -1;
            }
            if ((_ball->Position.y + _ball->Radius) >= Window::Height || (_ball->Position.y - _ball->Radius) <= 0)
            {
                _ball->Speed.y *= -1;
            }
            if ((_ball->Position.y + _ball->Radius) >= Window::Height - 5)
            {
                _player->Lives--;
                _dead = true;
            }
        }
        else
        {
            _ball->ResetSpeed();
            _ball->Position = { _player->Rec.x + _player->Rec.width / 2, _player->Rec.y - 10 };
        }
        _player->Rec.x = GetMousePosition().x;
        if (_player->Lives <= 0)
        {
            reset();
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            _dead = false;
        }
        if (CheckCollisionCircleRec(_ball->Position, _ball->Radius, _player->Rec))
        {
            _ball->Speed.y *= -1;
            if (_ball->Speed.x > 0)
            {
                _ball->Speed.x += (_ball->Position.x) / (_player->Rec.width / 2) * 2;
            }
            else
            {
                _ball->Speed.x -= (_ball->Position.x) / (_player->Rec.width / 2) * 2;
            }
        }
        bool allBricksDestroyed = true;
        for (Brick& b : _bricks)
        {
            if (b.Active && CheckCollisionCircleRec(_ball->Position, _ball->Radius, b.Rec))
            {
                b.Active = false;
                _player->Score += b.Score;
                if (_ball->Speed.y >= 0)
                {
                    _ball->Speed.y += b.Speed;
                }
                else
                {
                    _ball->Speed.y -= b.Speed;
                }
                _ball->Speed.y *= -1;
            }
            if (b.Active)
            {
                allBricksDestroyed = false;
            }
        }
        if (allBricksDestroyed)
        {
            nextLevel();
        }
    }
}

void App::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    for (Brick& b : _bricks)
    {
        if (b.Active)
        {
            DrawRectangleRec(b.Rec, b.Color);
        }
    }
    DrawCircleV(_ball->Position, _ball->Radius, RAYWHITE);
    DrawRectangleRec(_player->Rec, WHITE);
    DrawText(std::string("Lives: " + std::to_string(_player->Lives)).c_str(), (Window::Width - 40) - (MeasureText(std::string("Lives: " + std::to_string(_player->Lives)).c_str(), 24)), Window::Height - 40, 24, RAYWHITE);
    DrawText(std::string("Score: " + std::to_string(_player->Score)).c_str(), 20, Window::Height - 40, 24, RAYWHITE);
    DrawText(std::string("Level: " + std::to_string(_level)).c_str(), 20, Window::Height - 80, 24, RAYWHITE);
    EndDrawing();
    std::string text = (_paused ? "[PAUSED] " : "") + Window::Title + std::string(" - FPS: ") + std::to_string(GetFPS());
    SetWindowTitle(text.c_str());
}

void App::reset()
{
    _level = 0;
    _ball->ResetSpeed();
    _dead = true;
    _player->Lives = 5;
    _player->Score = 0;
    generateBricks();
}

void App::nextLevel()
{
    generateBricks();
    _ball->ResetSpeed();
    _level++;
}

inline const Color App::brickRowToColor(int br) const
{
    switch (br)
    {
    case 0:
        return PINK;
        break;
    case 1:
        return SKYBLUE;
        break;
    case 2:
        return VIOLET;
        break;
    case 3:
        return LIME;
        break;
    case 4:
        return ORANGE;
        break;
    default:
        return YELLOW;
        break;
    }
}

const void App::generateBricks()
{
    _bricks.clear();
    for (uint8_t i = 0; i < _rowsOfBricks; i++)
    {
        for (uint8_t j = 0; j < _bricksPerRow; j++)
        {
            Brick b;
            b.Rec = {
                static_cast<float_t>(j * _brickWidth + j * _brickPadding),
                static_cast<float_t>(i * _brickHeight + i * _brickPadding),
                static_cast<float_t>(_brickWidth),
                static_cast<float_t>(_brickHeight)
            };
            b.Active = true;
            b.Color = brickRowToColor(i);
            b.Score = (i + 5) * 5;
            b.Speed = (i + 5) * 2;
            _bricks.push_back(b);
        }
    }
}