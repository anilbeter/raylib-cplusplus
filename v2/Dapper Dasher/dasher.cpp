#include "raylib.h"

int main()
{

  const int windowWidth = 512;
  const int windowHeight = 380;

  InitWindow(windowWidth, windowHeight, "Dapper Dasher");

  // acceleration due to gravity (pixels/s)/s
  const int gravity = 1'000;

  // nebula variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
  Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
  Vector2 nebPos{
      windowWidth,
      windowHeight - (nebRec.height)};

  // nebula X velocity (pixels/second)
  int nebVel{-600};

  // scarfy variables
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

  // animation frame
  int frame;
  // amount of time before we update the animation frame
  const float updateTime = 1.0f / 12.0f;
  float runningTime;

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

    // update running time
    runningTime += dT;
    if (runningTime >= updateTime)
    {
      runningTime = 0.0f;
      // update animation frame
      scarfyRec.x = frame * scarfyRec.width;
      frame++;
      if (frame > 5)
      {
        frame = 0;
      }
    }

    // draw nebula
    DrawTextureRec(nebula, nebRec, nebPos, WHITE);

    // draw scarfy
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
    }

    // update nebula position
    nebPos.x += nebVel * dT;

    // update scarfy position
    scarfyPos.y += velocity * dT;

    EndDrawing();
  }
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
}