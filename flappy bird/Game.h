// Game.h
#pragma once
#include "Ball.h"
#include "Obstacle.h"
#include "Coin.h"
#include <vector>

class Game {
public:
    Game();
    void Run();           // main loop
private:
    void Update(float dt);
    void Draw() const;
    void Reset();

    Ball                 player;
    std::vector<Obstacle> obstacles;
    std::vector<Coin>     coins;
    float  scrollSpeed;
    double spawnTimer;
    int    score;
    static constexpr float BaseScroll = 150.0f;
};
