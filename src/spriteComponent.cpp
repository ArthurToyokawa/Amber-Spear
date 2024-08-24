#include "spriteComponent.hpp"

#include <iostream>

SpriteComponent::SpriteComponent(TextureEnum texture, int startingX, int startingY, int height, int width)
{
  objTexture = texture;

  pos.set(startingX, startingY);
  size.set(height, width);
  std::cout << "StartingXY: " << startingX << " " << startingY << std::endl;
}

void SpriteComponent::update(Vector2f physPos)
{
  pos.set((int)physPos.x + 0.5, (int)physPos.y + 0.5);
}
