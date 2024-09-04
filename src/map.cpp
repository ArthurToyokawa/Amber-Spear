#include "map.hpp"
#include "gameObjectGenerator.hpp"
#include "gameObject.hpp"

Map::Map(GameObjectGenerator *gen)
{
  gameObjectGenerator = gen;
  LoadMap(lvl1);
}

void Map::LoadMap(TextureEnum arr[20][25])
{
  std::cout << "loading map" << std::endl;
  for (int row = 0; row < 20; row++)
  {
    for (int column = 0; column < 25; column++)
    {
      int posX = column * 32;
      int posY = row * 32;
      int index = (row * 25) + column;
      switch (arr[row][column])
      {
        using enum TextureEnum;
      case rock:
        mapObjects[index] = gameObjectGenerator->makeRock(posX, posY);
        break;
      case lava:
        mapObjects[index] = gameObjectGenerator->makeLava(posX, posY);
        break;
      default:
        mapObjects[index] = gameObjectGenerator->makeRock(posX, posY);
        break;
      }
    }
  }
}