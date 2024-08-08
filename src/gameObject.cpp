#include "gameObject.hpp"
#include "textureManager.hpp"

#include <iostream>

GameObject::GameObject(const char *textureSheet, int startingX, int startingY, int height, int width, float friction, float mass)
{
  initialize(textureSheet, startingX, startingY, height, width, friction, mass);
}

GameObject::GameObject(const GameObjectProps &props)
{
  initialize(props.imagePath, props.posX, props.posY, props.width, props.height, props.rotation, props.mass);
}
// TODO REMOVER NOVA INICIALIZACAO SO COM ALIVE E XY
void GameObject::initialize(const char *textureSheet, int startingX, int startingY, int height, int width, float friction, float mass)
{
  alive = true;

  pos.set((float)startingX, (float)startingY);
  setSprite(textureSheet, startingX, startingY, height, width);
  setPhysics(0.0, 0.0, mass, 32, 32, friction);
}

void GameObject::updatePhysics(float time)
{
  pos = physics->update(time, pos);
}

void GameObject::updatePosition()
{
  sprite->update(pos);
}
