#include <iostream>

#include "menuItemGenerator.hpp"
#include "menuItem.hpp"
#include "menuText.hpp"

#include <common.hpp>
#include <globals.hpp>

MenuItem *MenuItemGenerator::makeStart(float posX, float posY)
{
  MenuItem *item = new MenuItem(posX, posY, START_GAME, "Iniciar");
  return item;
}
void MenuItemGenerator::START_GAME()
{
  gStageSystem.loadStage(1);
}

MenuItem *MenuItemGenerator::makeExit(float posX, float posY)
{
  MenuItem *item = new MenuItem(posX, posY, EXIT_GAME, "Sair");
  return item;
}
void MenuItemGenerator::EXIT_GAME()
{
  gGameStateSystem.stopRunning();
}

MenuItem *MenuItemGenerator::makeResume(float posX, float posY)
{
  MenuItem *item = new MenuItem(posX, posY, RESUME_GAME, "Resumir");
  return item;
}
void MenuItemGenerator::RESUME_GAME()
{
  gStageSystem.resumeFromMenu();
}

MenuItem *MenuItemGenerator::makeGoToMain(float posX, float posY)
{
  MenuItem *item = new MenuItem(posX, posY, GO_TO_MAIN, "Menu principal");
  return item;
}
void MenuItemGenerator::GO_TO_MAIN()
{
  gStageSystem.loadStage(100);
}

MenuItem *MenuItemGenerator::makeGoToScoreboard(float posX, float posY)
{
  MenuItem *item = new MenuItem(posX, posY, GO_TO_SCOREBOARD, "Pontuacoes");
  return item;
}
void MenuItemGenerator::GO_TO_SCOREBOARD()
{
  gStageSystem.loadStage(102);
}

MenuText *MenuItemGenerator::makeMenuText(float posX, float posY, const char *text)
{
  MenuText *item = new MenuText(posX, posY, text);
  return item;
}
