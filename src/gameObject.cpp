
#include "gameObject.hpp"
#include "textureManager.hpp"

#include <iostream>

GameObject::GameObject(
    const char *textureSheet,
    int startingX,
    int startingY,
    int height,
    int width)
{
  objTexture = TextureManager::LoadTexture(textureSheet);

  xpos = startingX;
  ypos = startingY;

  srcRect.h = height;
  srcRect.w = width;
  srcRect.x = 0;
  srcRect.y = 0;
  destRect.h = srcRect.h;
  destRect.w = srcRect.w;

  physics.initPhysics(0.0, 0.0, 0.0, 0.0, 3.0, 1, 1);
}

void GameObject::updatePhysics(float time)
{
  physics.update(time);
}
void GameObject::updatePosition()
{
  auto pos = physics.getPosition();
  xpos = (int)pos[0] + 0.5;
  ypos = (int)pos[1] + 0.5;
  destRect.x = xpos;
  destRect.y = ypos;
}

void GameObject::render()
{
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}