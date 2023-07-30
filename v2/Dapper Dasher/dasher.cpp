#include "raylib.h"

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main()
{

  const int windowWidth = 512;
  const int windowHeight = 380;

  InitWindow(windowWidth, windowHeight, "Dapper Dasher");

  // acceleration due to gravity (pixels/s)/s
  const int gravity = 1'000;

  // nebula variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  // AnimData for nebula
  AnimData nebData{
      {0.0, 0.0, nebula.width / 8, nebula.height / 8}, // Rectangle rec
      {windowWidth, windowHeight - nebula.height / 8}, // Vector2 pos
      0,                                               // int frame
      1.0 / 12.0,                                      // float updateTime
      0                                                // float runningTime
  };

  AnimData neb2Data{
      {0.0, 0.0, nebula.width / 8, nebula.height / 8},
      {windowWidth + 300, windowHeight - nebula.height / 8},
      0,
      1.0 / 16.0,
      0.0};

  // Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
  // Vector2 nebPos{windowWidth, windowHeight - (nebRec.height)};
  // int nebFrame = 0;
  // const float nebUpdateTime = 1.0f / 12.0f;
  // float nebRunningTime = 0;

  // Rectangle neb2Rec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
  // Vector2 neb2Pos{windowWidth + 300, windowHeight - (nebRec.height)};
  // int neb2Frame{};
  // const float neb2UpdateTime{1.0 / 16.0};
  // float neb2RunningTime{};

  // nebula X velocity (pixels/second)
  int nebVel{-200};

  // scarfy variables
  Texture2D scarfy = LoadTexture("textures/scarfy.png");
  AnimData scarfyData;
  scarfyData.rec.width = scarfy.width / 6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
  scarfyData.pos.y = windowHeight - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = 1.0 / 12.0;
  scarfyData.runningTime = 0.0;

  // Rectangle scarfyRec;
  // scarfyRec.width = scarfy.width / 6;
  // scarfyRec.height = scarfy.height;
  // scarfyRec.x = 0;
  // scarfyRec.y = 0;
  // Vector2 scarfyPos;
  // scarfyPos.x = (windowWidth / 2) - scarfyRec.width / 2;
  // scarfyPos.y = windowHeight - scarfyRec.height;

  int velocity = 0;

  bool isInAir;
  // jump velocity (pixels/s)
  const int jumpVel = -600;

  // scarfy animation frame
  // int frame;
  // amount of time before we update the animation frame
  // const float updateTime = 1.0f / 12.0f;
  // float runningTime;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // delta time (time since last frame)
    const float dT = GetFrameTime();

    // perform ground check
    if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
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
    scarfyData.runningTime += dT;
    // update scarfy's animation frame
    if (!isInAir)
    {
      if (scarfyData.runningTime >= scarfyData.updateTime)
      {
        scarfyData.runningTime = 0.0f;
        // update animation frame
        scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
        scarfyData.frame++;
        if (scarfyData.frame > 5)
        {
          scarfyData.frame = 0;
        }
      }
    }

    // update running time for nebula
    nebData.runningTime += dT;
    if (nebData.runningTime >= nebData.updateTime)
    {
      nebData.runningTime = 0.0f;
      nebData.rec.x = nebData.frame * nebData.rec.width;
      nebData.frame++;
      if (nebData.frame > 7)
      {
        nebData.frame = 0;
      }
    }

    // update running time for nebula
    neb2Data.runningTime += dT;
    if (neb2Data.runningTime >= neb2Data.updateTime)
    {
      neb2Data.runningTime = 0.0f;
      neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
      neb2Data.frame++;
      if (neb2Data.frame > 7)
      {
        neb2Data.frame = 0;
      }
    }

    // draw nebula
    DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
    // draw second nebula
    DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

    // draw scarfy
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
    }

    // update nebula position
    nebData.pos.x += nebVel * dT;
    // update second nebula position
    neb2Data.pos.x += nebVel * dT;

    // update scarfy position
    scarfyData.pos.y += velocity * dT;

    EndDrawing();
  }
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
}