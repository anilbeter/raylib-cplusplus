#include "raylib.h"

int main()
{

  const int windowWidth = 512;
  const int windowHeight = 380;

  InitWindow(windowWidth, windowHeight, "Dapper Dasher");

  // acceleration due to gravity (pixels/frame)/frame
  const int gravity = 1;

  // Rectangle dimensions
  const int width = 50;
  const int height = 80;

  int posY = windowHeight - height;
  int velocity = 0;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // perform ground check
    if (posY >= windowHeight - height)
    {
      // rectangle is on ground
      velocity = 0;
    }
    else
    {
      // rectangle is in the air
      // apply gravity
      velocity += gravity;
    }

    DrawRectangle(windowWidth / 2, posY, width, height, RED);
    if (IsKeyPressed(KEY_SPACE))
    {
      velocity -= 10;
    }

    // update position
    posY += velocity;

    EndDrawing();
  }
  CloseWindow();
}