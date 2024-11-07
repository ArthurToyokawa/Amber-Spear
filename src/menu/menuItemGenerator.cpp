#include <iostream>

#include "menuItemGenerator.hpp"
#include "menuItem.hpp"

#include <common.hpp>
#include <globals.hpp>

MenuItem *MenuItemGenerator::makeStart(float posX, float posY)
{
  MenuItem *item = new MenuItem(posX, posY, START_GAME, "Iniciar");
  return item;
}

MenuItem *MenuItemGenerator::makeExit(float posX, float posY)
{
  MenuItem *item = new MenuItem(posX, posY, EXIT_GAME, "Sair");
  return item;
}

void MenuItemGenerator::START_GAME()
{
  gStageSystem.loadStage(1);
}

void MenuItemGenerator::EXIT_GAME()
{
  gGameStateSystem.stopRunning();
}