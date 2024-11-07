
#include "menuManager.hpp"
#include "menuItem.hpp"
#include "common.hpp"
#include <gameObject/gameObject.hpp>
#include "globals.hpp"

void MenuManager::handleKeys(std::list<SDL_Keycode> keys)
{
  for (auto key : keys)
  {
    switch (key)
    {
    case SDLK_UP:
    case SDLK_w:
      if (currentKey != SDLK_UP || currentKeyCooldown <= 0)
      {
        currentKey = SDLK_UP;
        currentKeyCooldown = MAX_COOLDOWN;
        goMenuUp();
      }
      break;
    case SDLK_s:
    case SDLK_DOWN:
      if (currentKey != SDLK_DOWN || currentKeyCooldown <= 0)
      {
        currentKey = SDLK_DOWN;
        currentKeyCooldown = MAX_COOLDOWN;
        goMenuDown();
      }
      break;
    case SDLK_t:
    case SDLK_KP_ENTER:
    case SDLK_RETURN:
      if (currentKey != SDLK_RETURN || currentKeyCooldown <= 0)
      {
        currentKey = SDLK_RETURN;
        currentKeyCooldown = MAX_COOLDOWN;
        handleSelect();
      }
      break;
    case SDLK_y:
    case SDLK_BACKSPACE:
      if (currentKey != SDLK_BACKSPACE || currentKeyCooldown <= 0)
      {
        currentKey = SDLK_BACKSPACE;
        currentKeyCooldown = MAX_COOLDOWN;
        handleBack();
      }
      break;
    default:
      break;
    }
  }
}

void MenuManager::goMenuUp()
{
  currentItem = (currentItem == 0) ? maxItems : currentItem - 1;
}

void MenuManager::goMenuDown()
{
  currentItem = (currentItem == maxItems) ? currentItem = 0 : currentItem + 1;
}

void MenuManager::handleSelect()
{
  gMenuWorld.getMenuItemByIndex(currentItem)->triggerOnSelect();
};

void MenuManager::handleBack()
{
  std::cout << "Back item " << currentItem << std::endl;
};

void MenuManager::update(float time)
{
  currentKeyCooldown -= time;
}