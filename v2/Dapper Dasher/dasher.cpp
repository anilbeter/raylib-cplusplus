#include "raylib.h"

int main()
{

  const int windowWidth = 512;
  const int windowHeight = 380;

  InitWindow(windowWidth, windowHeight, "Dapper Dasher");

  // acceleration due to gravity (pixels/s)/s
  const int gravity = 1'000;

  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  Rectangle scarfyRec;
  scarfyRec.width = scarfy.width / 6;
  scarfyRec.height = scarfy.height;
  scarfyRec.x = 0;
  scarfyRec.y = 0;
  Vector2 scarfyPos;
  scarfyPos.x = (windowWidth / 2) - scarfyRec.width / 2;
  scarfyPos.y = windowHeight - scarfyRec.height;

  int velocity = 0;

  bool isInAir;
  // jump velocity (pixels/s)
  const int jumpVel = -600;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // delta time (time since last frame)
    const float dT = GetFrameTime();

    // perform ground check
    if (scarfyPos.y >= windowHeight - scarfyRec.height)
    {
      // rectangle is on ground
      velocity = 0;
      isInAir = false;
    }
    else
    {
      // rectangle is in the air
      // apply gravity
      velocity += gravity * dT;
      isInAir = true;
    }

    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
    }

    // update position
    scarfyPos.y += velocity * dT;

    EndDrawing();
  }
  UnloadTexture(scarfy);
  CloseWindow();
}