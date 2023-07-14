#include "raylib.h"

int main()
{
  const int windowWidth{512};
  const int windowHeight{380};
  SetTargetFPS(60);
  InitWindow(windowWidth, windowHeight, "BURNING UP!");

  // acceleration due to gravity (pixels/frame)/frame
  const int gravity{1};

  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  Rectangle scarfyRec;
  scarfyRec.width = scarfy.width / 6;
  scarfyRec.height = scarfy.height;
  scarfyRec.x = 0;
  scarfyRec.y = 0;
  Vector2 scarfyPos;
  scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
  scarfyPos.y = windowHeight - scarfyRec.height;

  int velocity{0};

  bool isInAir = true;
  const int jumpVel{-22};

  while (!WindowShouldClose())
  {
    // Start Drawing
    BeginDrawing();
    ClearBackground(WHITE);

    // perform ground check
    if (scarfyPos.y >= windowHeight - scarfyRec.height)
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
      velocity += jumpVel;
      isInAir = true;
    }

    // update position
    scarfyPos.y += velocity;

    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // Stop drawing
    EndDrawing();
  }
  UnloadTexture(scarfy);
  CloseWindow();
}