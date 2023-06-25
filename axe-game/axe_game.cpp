#include "raylib.h"

int main()
{
  // window dimensions
  int width{800};
  int height{450};
  InitWindow(width, height, "Anil's Window");
  // circle coordinates
  int circle_x{200};
  int circle_y{200};
  int circle_r{25};

  // axe coordinates
  int axe_x{400};
  int axe_y{0};

  SetTargetFPS(60);
  // window popup constantly open with this while loop
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Game logic begins

    // int width{800};
    // int height{450};
    DrawCircle(circle_x, circle_y, circle_r, BLUE);
    DrawRectangle(axe_x, axe_y, 50, 50, RED);

    // move the axe
    axe_y += 10;

    if (IsKeyDown(KEY_D) && circle_x < 775)
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