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
  int windowDimensions[2];
  windowDimensions[0] = 512;
  windowDimensions[1] = 380;

  // const int windowWidth = 512;
  // const int windowHeight = 380;

  InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

  // acceleration due to gravity (pixels/s)/s
  const int gravity = 1'000;

  // nebula variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

  const int sizeOfNebulae{10};
  AnimData nebulae[sizeOfNebulae]{};

  for (int i = 0; i < sizeOfNebulae; i++)
  {
    nebulae[i].rec.x = 0.0;
    nebulae[i].rec.y = 0.0;
    nebulae[i].rec.width = nebula.width / 8;
    nebulae[i].rec.height = nebula.height / 8;
    nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
    nebulae[i].frame = 0;
    nebulae[i].runningTime = 0.0;
    nebulae[i].updateTime = 1.0 / 16.0;
    nebulae[i].pos.x = windowDimensions[0] + i * 300;
  }

  // nebulae[0].pos.x = windowDimensions[0];
  // nebulae[1].pos.x = windowDimensions[0] + 300;
  // nebulae[2].pos.x = windowDimensions[0] + 600;

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
  scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
  scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
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
    if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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

    for (int i = 0; i < sizeOfNebulae; i++)
    {
      // update running time for nebula
      nebulae[i].runningTime += dT;
      if (nebulae[i].runningTime >= nebulae[i].updateTime)
      {
        nebulae[i].runningTime = 0.0f;
        nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
        nebulae[i].frame++;
        if (nebulae[i].frame > 7)
        {
          nebulae[i].frame = 0;
        }
      }
    }

    for (int i = 0; i < sizeOfNebulae; i++)
    {
      // draw each nebula
      DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
    }

    // draw nebula
    // DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
    // draw second nebula
    // DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

    // draw scarfy
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
    }

    for (int i = 0; i < sizeOfNebulae; i++)
    {
      // update the position of each nebula
      nebulae[i].pos.x += nebVel * dT;
    }

    // update nebula position
    // nebulae[0].pos.x += nebVel * dT;
    // update second nebula position
    // nebulae[1].pos.x += nebVel * dT;

    // update scarfy position
    scarfyData.pos.y += velocity * dT;

    EndDrawing();
  }
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
}
