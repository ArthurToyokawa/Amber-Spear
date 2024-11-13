#pragma once
#include <SDL2/SDL.h>

#include "list"

class MenuManager
{
public:
  MenuManager() {};

  int getCurrentItem() { return currentItem; };
  void setMaxItems(int maxI) { maxItems = maxI; };
  void setCurrentItem(int curr) { currentItem = curr; };

  void update(float time);
  void handleKeys(std::list<SDL_Keycode> keys);

  void goMenuUp();
  void goMenuDown();
  void handleSelect();
  void handleBack();

private:
  int currentItem = 0;
  int maxItems = 1;
  float currentKeyCooldown = 0.0;
  const float MAX_COOLDOWN = 0.2;
  SDL_Keycode currentKey = SDLK_F1;
};