#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "physicsComponent.hpp"
#include "spriteComponent.hpp"
#include "spellComponent.hpp"
#include "lifeComponent.hpp"
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

  Vector2f getPosition() { return pos; }
  EntityManager *getEntityManager() { return entityManager; }
  void setPosition(float posX, float posY) { pos.set(posX, posY); }

  void setPointsOnDeath(int p) { pointsOnDeath = p; };

  bool isAlive() { return alive; }
  bool isDead() { return !alive; }
  void kill();
  void removeChildren()
  {
    if (spell != nullptr)
    {
      delete spell;
      spell = nullptr;
    }
    if (life != nullptr)
    {
      delete life;
      life = nullptr;
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
      std::vector<SpriteAnimation *> anims)
  {
    sprite = new SpriteComponent(
        texture,
        startingX,
        startingY,
        height,
        width,
        anims);
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
  // Metodos de life
  void setLife(GameObject *gameObject, float maxLife, bool showLifeBar)
  {
    life = new LifeComponent(gameObject, maxLife, showLifeBar);
  }
  LifeComponent *getLife() { return life; }

private:
  bool alive;
  Vector2f pos;
  int pointsOnDeath = 0;

  SpriteComponent *sprite = nullptr;
  PhysicsComponent *physics = nullptr;
  SpellComponent *spell = nullptr;
  LifeComponent *life = nullptr;

  EntityManager *entityManager = nullptr;
  // TODO UMA FORMA DE COLISAO SECUNDARIO E IGNORAR A COLISAO DE FISICA
  //  std::function<void(GameObject *spell, GameObject *target, Vector2f overlap)> onCollision;
};
