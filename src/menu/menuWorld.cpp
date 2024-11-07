#include "menuWorld.hpp"
#include <menu/menuItem.hpp>

void MenuWorld::clearMenuItems()
{
  for (auto item : menuItems)
  {
    if (item)
    {
      delete item;
    }
  }
  menuItems.clear();
}

MenuItem *MenuWorld::getMenuItemByIndex(int index)
{
  if (index < 0 || static_cast<size_t>(index) >= menuItems.size())
  {
    return nullptr;
  }

  auto it = menuItems.begin();
  std::advance(it, index);
  return *it;
}