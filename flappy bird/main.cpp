#include "raylib.h"
#include "Game.h"

int main() {
    const int W = 800, H = 450;
    InitWindow(W, H, "Bounce Runner (clean version)");
    SetTargetFPS(60);

    Game g;
    g.Run();

    CloseWindow();
    return 0;
}
