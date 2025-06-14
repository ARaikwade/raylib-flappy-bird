// Ball.cpp
#include "Ball.h"

Ball::Ball(Vector2 start) { Reset(start); }
void Ball::Reset(Vector2 start) { pos = start; yVel = 0; }
void Ball::Jump() { yVel = JumpImpulse; }
void Ball::Update(float dt) {
    yVel += Gravity * dt;
    pos.y += yVel * dt;
    if (pos.y < Radius) { pos.y = Radius; yVel = 0; }
    if (pos.y > GetScreenHeight() - Radius) { pos.y = GetScreenHeight() - Radius; yVel = 0; }
}
void Ball::Draw() const { DrawCircleV(pos, Radius, DARKBLUE); }
Rectangle Ball::GetBBox() const { return { pos.x - Radius, pos.y - Radius, Radius * 2, Radius * 2 }; }
