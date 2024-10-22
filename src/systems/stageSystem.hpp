#pragma once
#include "array"

#include <textureEnumUtils.hpp>

class StageSystem
{

public:
  StageSystem()
  {
    currentStage = 0;
  };

  void loadStage(int stage);

  void removeWorldObjects();

private:
  int currentStage;

  // TODO TEM UM BUG QUE O MAPA NAO DA LOAD UMA SEGUNDA VEZ EU ACHO Q RESOLVE PASSANDO UMA REFERENCIA DO ARRAY
  void loadMap(const TextureEnum arr[20][25]);
  void loadStage1();
  void loadStage2();
  // void loadPlayer1Win();
  // void loadPlayer2Win();

  // MAPS
  const TextureEnum r = TextureEnum::rock;
  const TextureEnum l = TextureEnum::lava;

  const TextureEnum lvl1[20][25] = {
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

  const TextureEnum lvl2[20][25] = {
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