#include "raylib.h"

int main()
{
  const int windowWidth{512};
  const int windowHeight{380};
  SetTargetFPS(60);
  InitWindow(windowWidth, windowHeight, "BURNING UP!");

  // acceleration due to gravity (pixels/frame)/frame
  const int gravity{1};

  // rectangle dimensions
  const int width{50};
  const int height{80};

  int posY{windowHeight - height};
  int velocity{0};

  bool isInAir = true;

  while (!WindowShouldClose())
  {
    // Start Drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // perform ground check
    if (posY >= windowHeight - height)
    {
      // rectangle is on the ground
      velocity = 0;
      isInAir = false;
    }
    else
    {
      // rectange is in the air
      velocity += gravity;
    }

    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity -= 10;
      isInAir = true;
    }

    // update position
    posY += velocity;

    DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

    // Stop drawing
    EndDrawing();
  }
  CloseWindow();
}