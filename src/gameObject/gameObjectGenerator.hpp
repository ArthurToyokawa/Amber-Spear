#pragma once

#include <textureEnumUtils.hpp>
#include <my-lib/math-vector.h>
#include <vector>

class GameObject;
class SpriteAnimation;

using Vector2f = Mylib::Math::Vector<float, 2>;
class GameObjectGenerator
{
public:
  GameObjectGenerator() {}
  GameObject *makePlayer(float posX, float posY);
  GameObject *makeImpassableWall(float posX, float posY, float height, float width);
  GameObject *makeBox(float posX, float posY);
  GameObject *makeHeavyBox(float posX, float posY);
  GameObject *makeFireball(float playerPosX, float playerPosY, float playerAccX, float playerAccY);
  GameObject *makeRock(float posX, float posY);
  GameObject *makeLava(float posX, float posY);

  SpriteAnimation *makeZeroAnimation();
  std::vector<SpriteAnimation *> makeSingleSpriteAnimations();

private:
  // colisoes
  static void LAVA_COLISION(GameObject *spell, GameObject *target, Vector2f overlap);
  static void FIREBALL_COLISION(GameObject *spell, GameObject *target, Vector2f overlap);
};
