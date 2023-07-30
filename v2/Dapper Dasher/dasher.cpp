#include "raylib.h"

struct AnimData
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
  return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
  // update running time
  data.runningTime += deltaTime;
  if (data.runningTime >= data.updateTime)
  {
    data.runningTime = 0.0;
    // update animation frame
    data.rec.x = data.frame * data.rec.width;
    data.frame++;
    if (data.frame > maxFrame)
    {
      data.frame = 0;
    }
  }
  return data;
}

int main()
{
  int windowDimensions[2];
  windowDimensions[0] = 512;
  windowDimensions[1] = 380;

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
  scarfyData.updateTime = 1.0 / 6.0;
  scarfyData.runningTime = 0.0;

  int velocity = 0;
  Texture2D background = LoadTexture("textures/far-buildings.png");
  float bgX{};

  bool isInAir;
  // jump velocity (pixels/s)
  const int jumpVel = -600;

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    const float dT = GetFrameTime();
    BeginDrawing();
    ClearBackground(WHITE);

    bgX -= 20 * dT;
    if (bgX <= -background.width * 2)
    {
      bgX = 0.0;
    }

    // draw the background
    Vector2 bg1Pos{bgX, 0.0};
    DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
    Vector2 bg2Pos{bgX + background.width * 2, 0.0}; // 2 ile çarpıyorum çünkü DrawTextureEx de scale i 2 olarak aldım (2.0)
    DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

    // delta time (time since last frame)

    // perform ground check
    if (isOnGround(scarfyData, windowDimensions[1]))
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
      scarfyData = updateAnimData(scarfyData, dT, 5);
    }

    for (int i = 0; i < sizeOfNebulae; i++)
    {
      // update running time for nebula
      nebulae[i].runningTime += dT;
      if (nebulae[i].runningTime >= nebulae[i].updateTime)
      {
        nebulae[i] = updateAnimData(nebulae[i], dT, 7);
      }
    }

    for (int i = 0; i < sizeOfNebulae; i++)
    {
      // draw each nebula
      DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
    }

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
  UnloadTexture(background);
  CloseWindow();
}
