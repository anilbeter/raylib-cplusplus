#include "raylib.h"

int main()
{

  int windowDimensions[2];
  windowDimensions[0] = 384;
  windowDimensions[1] = 384;
  InitWindow(windowDimensions[0], windowDimensions[1], "Dream On");

  Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    Vector2 mapPos = {0.0, 0.0};
    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

    EndDrawing();
  }
  CloseWindow();
}