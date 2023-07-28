#include "raylib.h"

int main()
{
  // Window dimensions
  int windowWidth = 800;
  int windowHeight = 450;
  InitWindow(windowWidth, windowHeight, "Anil's Window");

  // Circle coordinates
  int circle_x = 200;
  int circle_y = 200;
  int circle_radius = 25;
  // circle edges
  int left_circle_x = circle_x - circle_radius;
  int right_circle_x = circle_x + circle_radius;
  int upper_circle_y = circle_y - circle_radius;
  int bottom_circle_y = circle_y + circle_radius;

  // Axe coordinates
  int axe_x = 400;
  int axe_y = 0;
  int axe_length = 50;
  // axe edges
  int l_axe_x = axe_x;
  int r_axe_x = axe_x + axe_length;
  int u_axe_y = axe_y;
  int b_axe_y = axe_y + axe_length;

  int direction = 10;

  bool collision_with_axe = (b_axe_y >= upper_circle_y) &&
                            (u_axe_y <= bottom_circle_y) &&
                            (r_axe_x >= left_circle_x) &&
                            (l_axe_x <= right_circle_x);

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    if (collision_with_axe)
    {
      DrawText("GAME OVER!", 240, windowHeight / 2, 52, RED);
    }
    else
    {
      // Game logic begins

      // update the edges
      left_circle_x = circle_x - circle_radius;
      right_circle_x = circle_x + circle_radius;
      upper_circle_y = circle_y - circle_radius;
      bottom_circle_y = circle_y + circle_radius;
      l_axe_x = axe_x;
      r_axe_x = axe_x + axe_length;
      u_axe_y = axe_y;
      b_axe_y = axe_y + axe_length;
      // update collision_with_axe
      collision_with_axe = (b_axe_y >= upper_circle_y) &&
                           (u_axe_y <= bottom_circle_y) &&
                           (r_axe_x >= left_circle_x) &&
                           (l_axe_x <= right_circle_x);

      DrawCircle(circle_x, circle_y, circle_radius, BLUE);
      if (IsKeyDown(KEY_D) && circle_x < windowWidth - circle_radius)
      {
        circle_x += 10;
      }
      if (IsKeyDown(KEY_A) && circle_x > 25)
      {
        circle_x -= 10;
      }
      DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);
      // move the axe
      axe_y += direction;
      if (axe_y > windowHeight || axe_y < 0)
      {
        direction = -direction;
        // Game logic ends
      }
    }
    EndDrawing();
  }
}