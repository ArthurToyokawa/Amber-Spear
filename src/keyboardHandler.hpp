#pragma once

#include "game.hpp"
#include <list>
#include "gameObject.hpp"

class KeyboardHandler
{
private:
  std::list<SDL_Keycode> activeKeys;
  GameObject *player;

  bool isKeyInList(SDL_Keycode key);

public:
  KeyboardHandler(GameObject *p);
  void handleKeyPress(SDL_Keycode key);
  void handleKeyRelease(SDL_Keycode key);
  std::list<SDL_Keycode> getActiveKeys();
};
