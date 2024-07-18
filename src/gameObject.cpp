
#include "gameObject.hpp"
#include "textureManager.hpp"

#include <iostream>

GameObject::GameObject(const char *textureSheet, int startingX, int startingY, int height, int width, float friction)
{
  initialize(textureSheet, startingX, startingY, height, width, friction);
}

GameObject::GameObject(const GameObjectProps &props)
{
  initialize(props.imagePath, props.posX, props.posY, props.width, props.height, props.rotation);
}

void GameObject::initialize(const char *textureSheet, int startingX, int startingY, int height, int width, float friction)
{
  alive = true;
  objTexture = TextureManager::LoadTexture(textureSheet);

  pos.set(startingX, startingY);
  std::cout << "StarntingXY" << startingX << " " << startingY << std::endl;

  srcRect.h = height;
  srcRect.w = width;
  srcRect.x = 0;
  srcRect.y = 0;
  destRect.h = srcRect.h;
  destRect.w = srcRect.w;
  destRect.x = startingX;
  destRect.y = startingY;
  physics.initPhysics((float)startingX, (float)startingY, 0.0, 0.0, 3.0, 1, 1, friction);
}

void GameObject::updatePhysics(float time)
{
  physics.update(time);
}
void GameObject::updatePosition()
{
  auto physPos = physics.getPosition();
  // transformando de float para int arredondando para o valor mais proximo
  pos.set((int)physPos[0] + 0.5, (int)physPos[1] + 0.5);
  destRect.x = pos.x;
  destRect.y = pos.y;
}

void GameObject::render()
{
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}