#pragma once
#include "array"

#include <textureEnumUtils.hpp>

class StageSystem
{

public:
  StageSystem()
  {
    currentStage = 0;
    isMenu = false;
    loadMap(lvl1);
  };

  bool isMenuStage() { return isMenu; };

  void loadStage(int stage);
  void resetStage();

  void removeWorldObjects();

private:
  int currentStage;
  bool isMenu = false;

  // TODO TEM UM BUG QUE O MAPA NAO DA LOAD UMA SEGUNDA VEZ EU ACHO Q RESOLVE PASSANDO UMA REFERENCIA DO ARRAY
  void loadMap(const TextureEnum arr[20][25]);
  void loadStage1();
  void loadStage2();

  void loadMainMenu();
  // void loadPauseMenu();
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