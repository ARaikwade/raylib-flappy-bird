// Ball.h
#pragma once
#include "raylib.h"

class Ball {
public:
    Ball(Vector2 startPos);
    void Update(float dt);
    void Jump();
    void Draw() const;
    void Reset(Vector2 startPos);
    Rectangle GetBBox() const;
private:
    Vector2 pos;
    float   yVel;
    static constexpr float Radius = 12.0f;
    static constexpr float Gravity = 900.0f;
    static constexpr float JumpImpulse = -400.0f;
};
