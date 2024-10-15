#pragma once
#include "array"
#include <my-lib/matrix.h>

#include <textureEnumUtils.hpp>
#include <globals.hpp>

class GameObjectGenerator;
class GameObject;
class MapManager
{
public:
  MapManager(GameObjectGenerator *gen);
  ~MapManager();
  // TODO usar matrix do mylib
  void LoadMap(TextureEnum arr[20][25]);

private:
  const TextureEnum r = TextureEnum::rock;
  const TextureEnum l = TextureEnum::lava;

  GameObjectGenerator *gameObjectGenerator;

  // TODO IMPLEMENTAR COM A BIBLIOTECA DE MATRIX
  //  Matrix<GameObject*> lvl1(20, 25);

  TextureEnum lvl1[20][25] = {
      {l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l, l},
      {l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l},
      {l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l},
      {l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l},
      {l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l},
      {l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l},
      {l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l},
      {l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l},
      {l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l},
      {l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l},
      {l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l},
      {l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l},
      {l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l},
      {l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l},
      {l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l},
      {l, l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l}};

  TextureEnum lvl2[20][25] = {
      {l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l, l},
      {l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l},
      {l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l},
      {l, l, l, l, r, r, r, l, l, l, r, r, r, r, r, l, l, l, r, r, r, l, l, l, l},
      {l, l, l, l, r, r, r, l, l, l, r, r, r, r, r, l, l, l, r, r, r, l, l, l, l},
      {l, l, l, l, r, r, r, l, l, l, r, r, r, r, r, l, l, l, r, r, r, l, l, l, l},
      {l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l},
      {l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l},
      {l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l},
      {l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l},
      {l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l},
      {l, l, l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, r, r, r, r, r, r, r, r, r, r, r, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, r, r, l, r, r, l, r, r, l, r, r, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, r, r, l, r, r, l, r, r, l, r, r, l, l, l, l, l, l, l},
      {l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l}};
};