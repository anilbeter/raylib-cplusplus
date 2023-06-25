#include "raylib.h"

int main()
{
  // window dimensions
  int width{350};
  int height{250};
  InitWindow(width, height, "Anil's Window");
  // circle coordinates
  int circle_x{175};
  int circle_y{100};
  int circle_r{25};

  SetTargetFPS(60);
  // window popup constantly open with this while loop
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Game logic begins

    DrawCircle(circle_x, circle_y, circle_r, BLUE);

    if (IsKeyDown(KEY_D) && circle_x < 325)
    {
      circle_x = circle_x + 10;
    }
    if (IsKeyDown(KEY_A) && circle_x > 25)
    {
      circle_x -= 10;
    }

    // Game logic ends
    EndDrawing();
  }
}