// Obstacle.h
#pragma once
#include "raylib.h"

struct Obstacle {
    Rectangle rect;
    static constexpr float Width = 60.0f;
    void Update(float dx) { rect.x -= dx; }
    void Draw() const { DrawRectangleRec(rect, RED); }
    bool IsOffScreen() const { return rect.x + rect.width < 0; }
};
