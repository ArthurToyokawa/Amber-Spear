#pragma once

#include <SDL2/SDL.h>
#include <list>

class KeyboardHandler
{
private:
  std::list<SDL_Keycode> activeKeys;

  bool isKeyInList(SDL_Keycode key);

public:
  KeyboardHandler();
  void handleKeyPress(SDL_Keycode key);
  void handleKeyRelease(SDL_Keycode key);
  std::list<SDL_Keycode> getActiveKeys();
};
