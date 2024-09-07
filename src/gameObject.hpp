#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "physicsComponent.hpp"
#include "spriteComponent.hpp"
#include "spellComponent.hpp"
#include "textureEnumUtils.hpp"
#include <my-lib/math-vector.h>
#include <functional>

class EntityManager;

using Vector2i = Mylib::Math::Vector<int, 2>;
using Vector2f = Mylib::Math::Vector<float, 2>;

class GameObject
{
public:
  GameObject(EntityManager *e, float startingX, float startingY);

  void updatePhysics(float time);
  void updateSprite();

  Vector2f getPosition()
  {
    return pos;
  }
  void setPosition(float posX, float posY)
  {
    pos.set(posX, posY);
  }
  bool isAlive() { return alive; }
  bool isDead() { return !alive; }
  void kill()
  {
    if (spell != nullptr)
    {
      delete spell;
      spell = nullptr;
    }
    if (physics != nullptr)
    {
      delete physics;
      physics = nullptr;
    }
    if (sprite != nullptr)
    {
      sprite->deleteAnimations();
      delete sprite;
      sprite = nullptr;
    }
    alive = false;
  }
  // metodos de colisao
  // bool ignorePhysicsCollision() {
  //   if(spell != nullptr) {
  //     return true;
  //   }
  // };
  //  Metodos de sprite
  void setSprite(
      TextureEnum texture,
      int startingX,
      int startingY,
      int height,
      int width,
      std::vector<SpriteAnimation *> anims,
      int defaultAnimationIndex)
  {
    sprite = new SpriteComponent(
        texture,
        startingX,
        startingY,
        height,
        width,
        anims,
        defaultAnimationIndex);
  }
  SpriteComponent *getSprite() { return sprite; }
  // Metodos de physics
  void setPhysics(
      float velX,
      float velY,
      float mass,
      float height,
      float width,
      float friction)
  {
    physics = new PhysicsComponent(
        velX,
        velY,
        mass,
        height,
        width,
        friction);
  }
  PhysicsComponent *getPhysics() { return physics; }
  // Metodos de spells
  void setSpell(std::function<void()> onCastFunc, std::function<void(GameObject *spell, GameObject *target, Vector2f overlap)> onCollisionFunc)
  {
    spell = new SpellComponent(onCastFunc, onCollisionFunc);
  }
  SpellComponent *getSpell() { return spell; }

private:
  bool alive;
  Vector2f pos;

  SpriteComponent *sprite = nullptr;
  PhysicsComponent *physics = nullptr;
  SpellComponent *spell = nullptr;
  EntityManager *entityManager = nullptr;
  // TODO UMA FORMA DE COLISAO SECUNDARIO E IGNORAR A COLISAO DE FISICA
  //  std::function<void(GameObject *spell, GameObject *target, Vector2f overlap)> onCollision;
};
