#pragma once
#include "array"
#include "textureEnumUtils.hpp"
#include <my-lib/matrix.h>

class GameObjectGenerator;
class GameObject;
class Map
{
public:
  Map(GameObjectGenerator *gen);
  ~Map();
  // TODO usar matrix do mylib
  void LoadMap(TextureEnum arr[20][25]);
  const std::array<GameObject *, 500> &getMapObjects() const { return mapObjects; }

private:
  const TextureEnum r = TextureEnum::rock;
  const TextureEnum l = TextureEnum::lava;

  GameObjectGenerator *gameObjectGenerator;
  std::array<GameObject *, 500> mapObjects;

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