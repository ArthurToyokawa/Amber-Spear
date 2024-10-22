#include <iostream>
#include "stageSystem.hpp"
#include "common.hpp"
#include <gameObject/gameObject.hpp>
#include <globals.hpp>

void StageSystem::loadStage(int stage)
{
  if (stage != currentStage)
  {
    std::cout << "Changing stage " << stage << std::endl;
    switch (stage)
    {
    case 1:
      currentStage = 1;
      loadStage1();
      break;
    case 2:
      currentStage = 2;
      loadStage2();
      break;
    default:
      std::cout << "Invalid stage" << std::endl;
      break;
    }
  }
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
