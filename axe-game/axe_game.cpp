#include "raylib.h"

int main()
{
  float root_beer;
  root_beer = 1.99f;
  double cheese_burger{5.99};
  bool shouldHaveLunch{};
  bool equal{4 == 9};        // false
  bool notEqual{4 != 9};     // true
  bool less{4 < 9};          // true
  bool lessEqual{4 <= 9};    // true
  bool greaterEqual{4 >= 9}; // false
  int width = 350;
  int height = 200;
  InitWindow(width, height, "Anil's Window");
}