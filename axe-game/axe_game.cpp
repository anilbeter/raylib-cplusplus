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
  // circle edges
  int l_circle_x{circle_x - circle_r};
  int r_circle_x{circle_x + circle_r};
  int u_circle_y{circle_y - circle_r};
  int b_circle_y{circle_y + circle_r};
  // axe coordinates
  int axe_x{400};
  int axe_y{0};
  int axe_length{50};
  // axe edges
  int l_axe_x{axe_x};
  int r_axe_x{axe_x + axe_length};
  int u_axe_y{axe_y};
  int b_axe_y{axe_y + axe_length};

  int direction{10};

  SetTargetFPS(60);
  bool collision_with_axe = true;
  // window popup constantly open with this while loop
  while (!WindowShouldClose())
  {

    BeginDrawing();
    ClearBackground(WHITE);

    if (collision_with_axe)
    {
      DrawText("Game Over!", 340, 225, 20, RED);
    }
    else
    {
      // Game logic begins

      // int width{800};
      // int height{450};
      DrawCircle(circle_x, circle_y, circle_r, BLUE);
      DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

      // move the axe
      axe_y += direction;
      if (axe_y > height || axe_y < 0)
      {
        direction = -direction;
      }

      if (IsKeyDown(KEY_D) && circle_x < width)
      {
        circle_x = circle_x + 10;
      }
      if (IsKeyDown(KEY_A) && circle_x > 0)
      {
        circle_x -= 10;
      }
    }
    EndDrawing();
  }
}