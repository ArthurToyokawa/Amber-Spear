#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "physicsComponent.hpp"
#include "spriteComponent.hpp"
#include "spellComponent.hpp"
#include "gameObjectProps.hpp"
#include <my-lib/math-vector.h>
#include <functional>

using Vector2i = Mylib::Math::Vector<int, 2>;
using Vector2f = Mylib::Math::Vector<float, 2>;

class GameObject
{
public:
  GameObject(float startingX, float startingY);

  void updatePhysics(float time);
  void updatePosition();

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
      delete sprite;
      sprite = nullptr;
    }
    alive = false;
  }
  // Metodos de sprite
  void setSprite(
      const char *textureSheet,
      int startingX,
      int startingY,
      int height,
      int width)
  {
    sprite = new SpriteComponent(
        textureSheet,
        startingX,
        startingY,
        height,
        width);
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
  void setSpell(std::function<void()> onCastFunc, std::function<void()> onCollisionFunc)
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
};
