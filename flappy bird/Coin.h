// Coin.h
#pragma once
#include "raylib.h"

struct Coin {
    Vector2 pos;
    static constexpr float Radius = 12.0f;
    void Update(float dx) { pos.x -= dx; }
    void Draw() const { DrawCircleV(pos, Radius, GOLD); }
    bool IsOffScreen() const { return pos.x + Radius < 0; }
};
