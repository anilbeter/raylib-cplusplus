#include "raylib.h"

int main()
{
  int width = 350;
  int height = 200;
  InitWindow(width, height, "Anil's Window");
  // window popup constantly open with this while loop
  while (true)
  {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
  }
}