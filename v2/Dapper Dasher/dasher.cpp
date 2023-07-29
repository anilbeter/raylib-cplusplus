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
  Rectangle nebRec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
  Vector2 nebPos{
      windowWidth,
      windowHeight - (nebRec.height)};

  Rectangle neb2Rec{0.0, 0.0, nebula.width / 8, nebula.height / 8};
  Vector2 neb2Pos{windowWidth + 300, windowHeight - (nebRec.height)};

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

  // nebula animation frame
  int nebFrame = 0;
  const float nebUpdateTime = 1.0f / 12.0f;
  float nebRunningTime = 0;

  int neb2Frame{};
  const float neb2UpdateTime{1.0 / 16.0};
  float neb2RunningTime{};

  // scarfy animation frame
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
    // update scarfy's animation frame
    if (runningTime >= updateTime && !isInAir)
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

    // update running time for nebula
    nebRunningTime += dT;
    if (nebRunningTime >= nebUpdateTime)
    {
      nebRunningTime = 0.0f;
      nebRec.x = nebFrame * nebRec.width;
      nebFrame++;
      if (nebFrame > 7)
      {
        nebFrame = 0;
      }
    }

    // update running time for nebula
    neb2RunningTime += dT;
    if (neb2RunningTime >= neb2UpdateTime)
    {
      neb2RunningTime = 0.0f;
      neb2Rec.x = neb2Frame * neb2Rec.width;
      neb2Frame++;
      if (neb2Frame > 7)
      {
        neb2Frame = 0;
      }
    }

    // draw nebula
    DrawTextureRec(nebula, nebRec, nebPos, WHITE);
    // draw second nebula
    DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

    // draw scarfy
    DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
    if (IsKeyPressed(KEY_SPACE) && !isInAir)
    {
      velocity += jumpVel;
    }

    // update nebula position
    nebPos.x += nebVel * dT;
    // update second nebula position
    neb2Pos.x += nebVel * dT;

    // update scarfy position
    scarfyPos.y += velocity * dT;

    EndDrawing();
  }
  UnloadTexture(scarfy);
  UnloadTexture(nebula);
  CloseWindow();
}