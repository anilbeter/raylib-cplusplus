#include <raylib.h>

int main()
{
  const int windowWidth{512};
  const int windowHeight{380};
  SetTargetFPS(60);
  InitWindow(windowWidth, windowHeight, "BURNING UP!");

  while (!WindowShouldClose())
  {
    // Start Drawing
    BeginDrawing();
    ClearBackground(RED);

    // Stop drawing
    EndDrawing();
  }
  CloseWindow();
}