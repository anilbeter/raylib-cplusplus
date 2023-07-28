#include "raylib.h"

int main()
{

  const int windowWidth = 512;
  const int windowHeight = 380;

  SetTargetFPS(60);
  InitWindow(windowWidth, windowHeight, "Dapper Dasher");
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
  }
  CloseWindow();
}