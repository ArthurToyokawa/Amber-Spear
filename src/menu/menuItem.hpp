#pragma once
#include <iostream>
#include <functional>
#include <my-lib/math-vector.h>
using Vector2i = Mylib::Math::Vector<int, 2>;

class MenuItem
{
public:
  MenuItem(int posX, int posY, std::function<void()> onSelectFunc, const char *displayText)
  {
    pos.set(posX, posY);
    onSelect = onSelectFunc;
    text = displayText;
  }

  const char *getText() { return text; };
  Vector2i getPos() { return pos; };
  void triggerOnSelect() { onSelect(); };

private:
  Vector2i pos;
  std::function<void()> onSelect;
  const char *text;
};
