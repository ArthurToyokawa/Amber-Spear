#include "mapManager.hpp"
#include "gameObjectGenerator.hpp"
#include "gameObject.hpp"

MapManager::MapManager(GameObjectGenerator *gen)
{
  gameObjectGenerator = gen;
  LoadMap(lvl1);
}

void MapManager::LoadMap(TextureEnum arr[20][25])
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
      switch (arr[row][column])
      {
        using enum TextureEnum;
      case rock:
        mapObjs[index] = gameObjectGenerator->makeRock(posX, posY);
        break;
      case lava:
        mapObjs[index] = gameObjectGenerator->makeLava(posX, posY);
        break;
      default:
        mapObjs[index] = gameObjectGenerator->makeRock(posX, posY);
        break;
      }
    }
  }
}