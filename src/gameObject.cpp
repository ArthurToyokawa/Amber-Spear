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

void GameObject::initialize(const char *textureSheet, int startingX, int startingY, int height, int width, float friction, float mass)
{
  alive = true;
  objTexture = TextureManager::LoadTexture(textureSheet);

  pos.set(startingX, startingY);
  std::cout << "StartingXY" << startingX << " " << startingY << std::endl;

  srcRect.h = height;
  srcRect.w = width;
  srcRect.x = 0;
  srcRect.y = 0;
  destRect.h = srcRect.h;
  destRect.w = srcRect.w;
  destRect.x = startingX;
  destRect.y = startingY;

  physics.initPhysics((float)startingX, (float)startingY, 0.0, 0.0, mass, 32, 32, friction);
}

void GameObject::updatePhysics(float time)
{
  physics.update(time);
}

void GameObject::updatePosition()
{
  auto physPos = physics.getPosition();
  pos.set((int)physPos[0] + 0.5, (int)physPos[1] + 0.5);
  destRect.x = pos.x;
  destRect.y = pos.y;
}

void GameObject::render()
{
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
