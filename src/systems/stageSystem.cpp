#include <iostream>
#include "stageSystem.hpp"
#include "common.hpp"
#include <gameObject/gameObject.hpp>
#include <scoreboard/score.hpp>
#include <globals.hpp>
#include <list>

void StageSystem::loadStage(int stage)
{
  if (stage != currentStage)
  {
    std::cout << "Changing stage " << stage << std::endl;
    switch (stage)
    {
    case 1:
      currentStage = 1;
      isMenu = false;
      loadStage1();
      break;
    case 2:
      currentStage = 2;
      isMenu = false;
      loadStage2();
      break;
    case 100:
      currentStage = 100;
      isMenu = true;
      loadMainMenu();
      break;
    case 101:
      currentStage = 101;
      isMenu = true;
      loadPauseMenu();
    case 102:
      currentStage = 102;
      isMenu = true;
      loadScoreboard();
      break;
    default:
      std::cout << "Invalid stage" << std::endl;
      break;
    }
  }
}

void StageSystem::resetStage()
{
  int currStage = currentStage;
  currentStage = -1;
  loadStage(currStage);
}

void StageSystem::resumeFromMenu()
{
  if (isMenu)
  {
    isMenu = false;
    currentStage = -1;
  }
}

void StageSystem::loadMainMenu()
{
  std::cout << "Loading Main menu" << std::endl;

  gMenuWorld.clearMenuItems();

  MenuItem *start = gMenuItemGenerator.makeStart(250.0, 200.0);
  gMenuWorld.getMenuItems().push_back(start);

  MenuItem *score = gMenuItemGenerator.makeGoToScoreboard(250.0, 300.0);
  gMenuWorld.getMenuItems().push_back(score);

  MenuItem *exit = gMenuItemGenerator.makeExit(250.0, 400.0);
  gMenuWorld.getMenuItems().push_back(exit);

  gMenuManager.setCurrentItem(0);
  gMenuManager.setMaxItems(2);
  // TODO CARREGAR MUSICA BASEADO NO NIVEL
  gSoundSystem.playMusic(0);
}

void StageSystem::loadPauseMenu()
{
  std::cout << "Loading Pause menu" << std::endl;

  gMenuWorld.clearMenuItems();

  MenuItem *resume = gMenuItemGenerator.makeResume(250.0, 200.0);
  gMenuWorld.getMenuItems().push_back(resume);

  MenuItem *goToMain = gMenuItemGenerator.makeGoToMain(250.0, 400.0);
  gMenuWorld.getMenuItems().push_back(goToMain);

  gMenuManager.setCurrentItem(0);
  gMenuManager.setMaxItems(1);
}

void StageSystem::loadScoreboard()
{
  std::cout << "Loading Scoreboard" << std::endl;

  gMenuWorld.clearMenuItems();
  std::list<Score *> testScores;
  testScores = gFileManager.readFile();
  float scoreX = 250.0;
  float scoreY = 200.0;

  for (auto it = testScores.begin(); it != testScores.end();)
  {
    auto &obj = *it;
    std::cout << obj->getScoreString() << std::endl;
    MenuText *score = gMenuItemGenerator.makeMenuText(
        scoreX,
        scoreY,
        obj->getScoreString());
    gMenuWorld.getMenuTexts().push_back(score);
    scoreY += 30.0;
    ++it;
  }

  MenuItem *goToMain = gMenuItemGenerator.makeGoToMain(250.0, 400.0);
  gMenuWorld.getMenuItems().push_back(goToMain);

  gMenuManager.setCurrentItem(0);
  gMenuManager.setMaxItems(1);
}

void StageSystem::loadStage1()
{
  std::cout << "Loading stage 1" << std::endl;
  // gWorld.clearMapObjects();
  loadMap(lvl1);

  gWorld.clearSpells();
  gWorld.clearPlayers();
  // TODO TODO X.0 MUDAR PARA X.0f para setar como float
  gWorld.getPlayer() = gGameObjectGenerator->makePlayer(128.0, 256.0);

  // gWorld.clearObjects();
  GameObject *box = gGameObjectGenerator->makeBox(250.0, 300.0);
  gWorld.getObjects().push_back(box);
  GameObject *hBox = gGameObjectGenerator->makeHeavyBox(350.0, 300.0);
  gWorld.getObjects().push_back(hBox);

  GameObject *wallLeft = gGameObjectGenerator->makeImpassableWall(-100, 0.0, SCREEN_HEIGHT, 100);
  gWorld.getObjects().push_back(wallLeft);
  GameObject *wallRight = gGameObjectGenerator->makeImpassableWall(SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 100);
  gWorld.getObjects().push_back(wallRight);
  GameObject *wallUp = gGameObjectGenerator->makeImpassableWall(0.0, -100, 100, SCREEN_WIDTH);
  gWorld.getObjects().push_back(wallUp);
  GameObject *wallDown = gGameObjectGenerator->makeImpassableWall(0.0, SCREEN_HEIGHT, 100, SCREEN_WIDTH);
  gWorld.getObjects().push_back(wallDown);

  // TODO CARREGAR MUSICA BASEADO NO NIVEL
  gSoundSystem.playMusic(0);
}

void StageSystem::loadStage2()
{
  std::cout << "Loading stage 2" << std::endl;
  // gWorld.clearMapObjects();
  loadMap(lvl2);

  gWorld.clearSpells();
  gWorld.clearPlayers();
  // TODO TODO X.0 MUDAR PARA X.0f para setar como float
  gWorld.getPlayer() = gGameObjectGenerator->makePlayer(128.0, 160.0);
  gWorld.getPlayer2() = gGameObjectGenerator->makePlayer(640.0, 160.0);

  gWorld.clearObjects();
  GameObject *box = gGameObjectGenerator->makeBox(336.0, 300.0);
  gWorld.getObjects().push_back(box);
  GameObject *box2 = gGameObjectGenerator->makeBox(432.0, 300.0);
  gWorld.getObjects().push_back(box2);
  GameObject *hBox = gGameObjectGenerator->makeHeavyBox(336.0, 200.0);
  gWorld.getObjects().push_back(hBox);
  GameObject *hBox2 = gGameObjectGenerator->makeHeavyBox(432.0, 200.0);
  gWorld.getObjects().push_back(hBox2);

  GameObject *wallLeft = gGameObjectGenerator->makeImpassableWall(-100, 0.0, SCREEN_HEIGHT, 100);
  gWorld.getObjects().push_back(wallLeft);
  GameObject *wallRight = gGameObjectGenerator->makeImpassableWall(SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 100);
  gWorld.getObjects().push_back(wallRight);
  GameObject *wallUp = gGameObjectGenerator->makeImpassableWall(0.0, -100, 100, SCREEN_WIDTH);
  gWorld.getObjects().push_back(wallUp);
  GameObject *wallDown = gGameObjectGenerator->makeImpassableWall(0.0, SCREEN_HEIGHT, 100, SCREEN_WIDTH);
  gWorld.getObjects().push_back(wallDown);

  // TODO CARREGAR MUSICA BASEADO NO NIVEL
  gSoundSystem.playMusic(0);
}

// MAPS
void StageSystem::loadMap(const TextureEnum arr[20][25])
{
  std::cout << "loading map" << std::endl;
  for (int row = 0; row < 20; row++)
  {
    for (int column = 0; column < 25; column++)
    {
      int posX = column * 32;
      int posY = row * 32;
      int index = (row * 25) + column;
      std::array<GameObject *, 500> &mapObjs = gWorld.getMapObjects();
      if (mapObjs[index] != nullptr)
      {
        mapObjs[index]->removeChildren();
        delete mapObjs[index];
        mapObjs[index] = nullptr;
      }
      switch (arr[row][column])
      {
        using enum TextureEnum;
      case rock:
        mapObjs[index] = gGameObjectGenerator->makeRock(posX, posY);
        break;
      case lava:
        mapObjs[index] = gGameObjectGenerator->makeLava(posX, posY);
        break;
      default:
        mapObjs[index] = gGameObjectGenerator->makeRock(posX, posY);
        break;
      }
    }
  }
}
