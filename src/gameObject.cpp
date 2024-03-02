
#include "gameObject.hpp"
#include "textureManager.hpp"

GameObject::GameObject(const char *textureSheet, int startingX, int startingY)
{
  objTexture = TextureManager::LoadTexture(textureSheet);

  xpos = startingX;
  ypos = startingY;
}

void GameObject::update()
{
  xpos++;
  ypos++;
  // TODO pegar os dados do objeto na criacao
  srcRect.h = 32;
  srcRect.w = 32;
  srcRect.x = 0;
  srcRect.y = 0;

  destRect.x = xpos;
  destRect.y = ypos;
  destRect.h = srcRect.h;
  destRect.w = srcRect.w;
}

void GameObject::render()
{
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}