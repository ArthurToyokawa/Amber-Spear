#pragma once
#include <iostream>
#include <my-lib/math-vector.h>
using Vector2i = Mylib::Math::Vector<int, 2>;

class MenuText
{
public:
  MenuText(int posX, int posY, const char *displayText)
  {
    pos.set(posX, posY);
    text = displayText;
  }

  const char *getText() { return text; };
  Vector2i getPos() { return pos; };

private:
  Vector2i pos;
  const char *text;
};
