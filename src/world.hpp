#pragma once
#include <SDL2/SDL.h>
#include "list"
#include "array"

class GameObject;

class World
{
public:
  World() {};

  GameObject *&getPlayer() { return player; };
  // TODO MUDAR TODOS OS PONTEIROS PARA SMART POINTERS
  // std::weak_ptr<GameObject> getPlayerPt() { return std::weak_ptr<GameObject>(playerPt); }

  std::list<GameObject *> &getSpells() { return spells; };
  std::list<GameObject *> &getObjects() { return objects; };
  std::array<GameObject *, 500> &getMapObjects() { return mapObjects; };

  void clearSpells();

  void clearObjects();
  // esse metodo n é usado no momento
  void clearMapObjects();

  void clearPlayers();

private:
  GameObject *player;
  // TODO MUDAR TODOS OS PONTEIROS PARA SMART POINTERS
  //  std::shared_ptr<GameObject> playerPt;
  std::list<GameObject *> spells;
  std::list<GameObject *> objects;
  std::array<GameObject *, 500> mapObjects;
};
