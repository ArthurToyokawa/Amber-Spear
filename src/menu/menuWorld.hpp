#pragma once
#include <SDL2/SDL.h>
#include "list"

class MenuItem;
class MenuText;

class MenuWorld
{
public:
  MenuWorld() {};

  std::list<MenuItem *> &getMenuItems() { return menuItems; };
  std::list<MenuText *> &getMenuTexts() { return menuTexts; };
  MenuItem *getMenuItemByIndex(int index);
  void clearMenuItems();

private:
  std::list<MenuItem *> menuItems;
  std::list<MenuText *> menuTexts;
};
