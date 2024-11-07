#pragma once
#include <SDL2/SDL.h>
#include "list"

class MenuItem;

class MenuWorld
{
public:
  MenuWorld() {};

  std::list<MenuItem *> &getMenuItems() { return menuItems; };
  MenuItem *getMenuItemByIndex(int index);
  void clearMenuItems();

private:
  std::list<MenuItem *> menuItems;
};
