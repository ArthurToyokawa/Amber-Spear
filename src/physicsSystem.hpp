#pragma once
#include <SDL2/SDL.h>

#include "list"
#include "gameObject.hpp"
#include <my-lib/math-vector.h>

using Vector2f = Mylib::Math::Vector<float, 2>;

struct ObjectsCollision
{
  bool haveCollided;
  Vector2f overlap;
};

class PhysicsSystem
{
public:
  void handleCollisions(GameObject *player, std::list<GameObject *> spells, std::list<GameObject *> objects);
  Vector2f getCollisionOverlap(GameObject *a, GameObject *b);
  ObjectsCollision haveObjectsCollided(GameObject *a, GameObject *b);
  void resolveCollision(GameObject *a, GameObject *b, Vector2f overlap);
  void resolveSpellCollision(GameObject *a, GameObject *b, Vector2f overlap);
  void resolveObjectsCollision(GameObject *a, GameObject *b, Vector2f overlap);
  void teleportObjectsOutOfCollision(GameObject *a, GameObject *b, Vector2f overlap);
};