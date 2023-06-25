#include "raylib.h"

int main()
{
  int width = 350;
  int height = 200;
  InitWindow(width, height, "Anil's Window");
  // window popup constantly open with this while loop

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawCircle(175, 100, 25, BLUE);
    EndDrawing();
  }
}