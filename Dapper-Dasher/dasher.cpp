#include "raylib.h"

int main()
{
  const int windowWidth{512};
  const int windowHeight{380};
  SetTargetFPS(60);
  InitWindow(windowWidth, windowHeight, "BURNING UP!");

  // rectangle dimensions
  const int width{50};
  const int height{80};

  int posY{windowHeight - height};
  int velocity{0};

  while (!WindowShouldClose())
  {
    // Start Drawing
    BeginDrawing();
    ClearBackground(WHITE);

    if (IsKeyPressed(KEY_SPACE))
    {
      velocity -= 10;
    }
    posY += velocity;

    DrawRectangle(windowWidth / 2, posY, width, height, BLUE);

    // Stop drawing
    EndDrawing();
  }
  CloseWindow();
}