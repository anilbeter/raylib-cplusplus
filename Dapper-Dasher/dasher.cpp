#include "raylib.h"

int main()
{
  const int windowWidth{512};
  const int windowHeight{380};
  SetTargetFPS(60);
  InitWindow(windowWidth, windowHeight, "BURNING UP!");

  // acceleration due to gravity (pixels/s)/frame
  const int gravity{1'000};

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

  // animation frame
  int frame{};
  float updateTime{1.0 / 12.0};
  float runningTime{};

  bool isInAir = true;

  // pixels/s
  const int jumpVel{-600};

  while (!WindowShouldClose())
  {
    // delta time
    const float dT{GetFrameTime()};

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
      velocity += gravity * dT;
    }

    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
      isInAir = true;
    }

    // update position
    scarfyPos.y += velocity * dT;

    // update running time
    runningTime += dT;
    if (runningTime >= updateTime)
    {
      runningTime = 0;
      // update animation frame
      scarfyRec.x = frame * scarfyRec.width;
      frame++;
      if (frame > 5)
      {
        frame = 0;
      }
    }

    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

    // Stop drawing
    EndDrawing();
  }
  UnloadTexture(scarfy);
  CloseWindow();
}