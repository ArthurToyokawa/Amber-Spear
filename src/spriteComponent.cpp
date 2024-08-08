#include "spriteComponent.hpp"
#include "textureManager.hpp"

#include <iostream>

SpriteComponent::SpriteComponent(const char *textureSheet, int startingX, int startingY, int height, int width)
{
  objTexture = TextureManager::LoadTexture(textureSheet);

  pos.set(startingX, startingY);
  std::cout << "StartingXY: " << startingX << " " << startingY << std::endl;

  srcRect.h = height;
  srcRect.w = width;
  srcRect.x = 0;
  srcRect.y = 0;
  destRect.h = srcRect.h;
  destRect.w = srcRect.w;
  destRect.x = startingX;
  destRect.y = startingY;
}

void SpriteComponent::update(Vector2f physPos)
{
  pos.set((int)physPos.x + 0.5, (int)physPos.y + 0.5);
  destRect.x = pos.x;
  destRect.y = pos.y;
}

void SpriteComponent::render()
{
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
