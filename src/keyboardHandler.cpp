#include "keyboardHandler.hpp"

KeyboardHandler::KeyboardHandler()
{
}

bool KeyboardHandler::isKeyInList(SDL_Keycode key)
{
  bool inList = false;
  for (auto k : activeKeys)
  {
    if (k == key)
    {
      inList = true;
    }
  }
  return inList;
}

void KeyboardHandler::handleKeyPress(SDL_Keycode key)
{

  if (!isKeyInList(key))
  {
    activeKeys.push_front(key);
  }
}
void KeyboardHandler::handleKeyRelease(SDL_Keycode key)
{
  if (isKeyInList(key))
  {
    activeKeys.remove(key);
  }
}
std::list<SDL_Keycode> KeyboardHandler::getActiveKeys()
{
  // print keys
  //  std::cout << "Active Keys: ";
  //    for (auto key : kHandler->getActiveKeys())
  //  {
  //  std::cout << key << " ";
  //  }
  //  std::cout << std::endl;
  return activeKeys;
}