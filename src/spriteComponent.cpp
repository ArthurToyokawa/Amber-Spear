#include "spriteComponent.hpp"

#include <iostream>

SpriteComponent::SpriteComponent(TextureEnum texture, int startingX, int startingY, int height, int width, std::vector<SpriteAnimation *> anims, int defaultAnimationIndex)
{
  // std::cout << "StartingXY: " << startingX << " " << startingY << std::endl;
  objTexture = texture;

  pos.set(startingX, startingY);
  size.set(height, width);
  animations = anims;
  animationIndex = 0;
}

void SpriteComponent::update(Vector2f physPos)
{
  pos.set((int)physPos.x + 0.5, (int)physPos.y + 0.5);
}

void SpriteComponent::deleteAnimations()
{
  for (SpriteAnimation *animation : animations)
  {
    delete animation;
  }
  animations.clear();
}
