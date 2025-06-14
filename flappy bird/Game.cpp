// Game.cpp
#include "Game.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

static float Rand01() { return (float)std::rand() / RAND_MAX; }

Game::Game()
    : player({ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 })
{
    std::srand(static_cast<unsigned>(time(nullptr)));
    Reset();
}

void Game::Reset() {
    obstacles.clear();
    coins.clear();
    player.Reset({ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 });
    spawnTimer = 0.0;
    scrollSpeed = BaseScroll;
    score = 0;
}

void Game::Run() {
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Update(dt);
        Draw();
    }
}

void Game::Update(float dt) {
    // input
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE)) player.Jump();
    if (IsKeyDown(KEY_LEFT))  scrollSpeed = BaseScroll - 100;
    else if (IsKeyDown(KEY_RIGHT)) scrollSpeed = BaseScroll + 100;
    else scrollSpeed = BaseScroll;

    // physics
    player.Update(dt);

    // spawn
    spawnTimer += dt;
    if (spawnTimer > 1.2f) {
        spawnTimer = 0;
        float h = 80 + Rand01() * 180;
        float y = GetScreenHeight() - h;
        obstacles.push_back({ Rectangle{ (float)GetScreenWidth() + Obstacle::Width, y, Obstacle::Width, h } });
        if (std::rand() % 10 < 6) {
            coins.push_back({ Vector2{ (float)GetScreenWidth() + Obstacle::Width + 30, y - 120 + Rand01() * 80 } });
        }
    }

    // move & trim
    for (auto& o : obstacles) o.Update(scrollSpeed * dt);
    for (auto& c : coins)     c.Update(scrollSpeed * dt);
    while (!obstacles.empty() && obstacles.front().IsOffScreen()) obstacles.erase(obstacles.begin());
    while (!coins.empty() && coins.front().IsOffScreen())     coins.erase(coins.begin());

    // collisions
    Rectangle bb = player.GetBBox();
    for (const auto& o : obstacles)
        if (CheckCollisionRecs(bb, o.rect)) { Reset(); return; }

    for (size_t i = 0; i < coins.size();) {
        if (CheckCollisionCircleRec(coins[i].pos, Coin::Radius, bb)) { score++; coins.erase(coins.begin() + i); }
        else ++i;
    }
}

void Game::Draw() const {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (const auto& o : obstacles) o.Draw();
    for (const auto& c : coins)     c.Draw();
    player.Draw();
    DrawText(TextFormat("Score: %d", score), 20, 20, 28, BLACK);
    DrawFPS(GetScreenWidth() - 90, 10);
    EndDrawing();
}
