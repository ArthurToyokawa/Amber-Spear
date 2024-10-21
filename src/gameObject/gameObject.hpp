#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <my-lib/math-vector.h>
#include <functional>

#include "physicsComponent.hpp"
#include "spriteComponent.hpp"
#include "spellComponent.hpp"
#include "lifeComponent.hpp"
#include "auraComponent.hpp"
#include "textureEnumUtils.hpp"

using Vector2i = Mylib::Math::Vector<int, 2>;
using Vector2f = Mylib::Math::Vector<float, 2>;

class GameObject
{
public:
  GameObject(float startingX, float startingY);

  void updatePhysics(float time);
  void updateSprite();
  void updateAuras(float time);

  Vector2f getPosition() { return pos; }
  void setPosition(float posX, float posY) { pos.set(posX, posY); }

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
    for (auto &aura : auras)
    {
      delete aura;
    }
    auras.clear();
  }
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
      float friction,
      bool intangible,
      bool unstoppable)
  {
    physics = new PhysicsComponent(
        velX,
        velY,
        mass,
        height,
        width,
        friction,
        intangible,
        unstoppable);
  }
  PhysicsComponent *getPhysics() { return physics; }
  // Metodos de spells
  void setSpell(std::function<void()> onCastFunc, std::function<void(GameObject *spell, GameObject *target, Vector2f overlap)> onCollisionFunc)
  {
    spell = new SpellComponent(onCastFunc, onCollisionFunc);
  }
  SpellComponent *getSpell() { return spell; }
  // Metodos de life
  void setLife(GameObject *gameObject, float maxLife, bool showLifeBar, int pointsOnDeath)
  {
    life = new LifeComponent(gameObject, maxLife, showLifeBar, pointsOnDeath);
  }
  LifeComponent *getLife() { return life; }
  // Metodos de aura
  bool hasAura(int auraId)
  {
    for (const auto &aura : auras)
    {
      if (aura->getAuraId() == auraId)
      {
        return true;
      }
    }
    return false;
  }
  void addAura(int auraId, float duration, TextureEnum auraTexture, std::function<void(GameObject *)> onStartFunc, std::function<void(GameObject *)> onEndFunc)
  {
    AuraComponent *newAura = new AuraComponent(this, auraId, duration, auraTexture, onStartFunc, onEndFunc);
    auras.push_back(newAura);
  }
  void removeAura(AuraComponent *aura)
  {
    auras.remove(aura);
    delete aura;
  }
  std::list<AuraComponent *> getAuras() { return auras; }

private:
  bool alive;
  Vector2f pos;

  SpriteComponent *sprite = nullptr;
  PhysicsComponent *physics = nullptr;
  SpellComponent *spell = nullptr;
  LifeComponent *life = nullptr;
  std::list<AuraComponent *> auras;
};
