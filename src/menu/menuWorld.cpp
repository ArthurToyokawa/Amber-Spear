#include "menuWorld.hpp"
#include <menu/menuItem.hpp>
#include <menu/menuText.hpp>

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
  for (auto text : menuTexts)
  {
    if (text)
    {
      delete text;
    }
  }
  menuTexts.clear();
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