#pragma once
#include <iostream>
#include <functional>
#include <my-lib/math-vector.h>
using Vector2i = Mylib::Math::Vector<int, 2>;

class MenuItem
{
public:
  MenuItem(int posX, int posY, std::function<void()> onSelectFunc, char *displayText)
  {
    pos.set(posX, posY);
    onSelect = onSelectFunc;
    text = displayText;
  }

  char *getText() { return text; };
  Vector2i getPos() { return pos; };
  void triggerOnSelect() { onSelect(); };

private:
  Vector2i pos;
  std::function<void()> onSelect;
  char *text;
};
