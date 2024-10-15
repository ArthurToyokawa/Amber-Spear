#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include <my-lib/math-vector.h>

#include <textureEnumUtils.hpp>
#include "spriteAnimation.hpp"

using Vector2i = Mylib::Math::Vector<int, 2>;
using Vector2f = Mylib::Math::Vector<float, 2>;

class SpriteComponent
{
public:
  SpriteComponent(TextureEnum texture, int startingX, int startingY, int height, int width, std::vector<SpriteAnimation *> anims);

  void update(Vector2f physPos);
  int getX() { return pos.x; }
  int getY() { return pos.y; }
  int getWidth() { return size.x; }
  int getHeight() { return size.y; }
  TextureEnum getTexture() { return objTexture; }
  void deleteAnimations();

  SpriteAnimation *getCurrentAnimation()
  {
    return animations[animationIndex];
  }
  void switchAnimation(int index)
  {
    // std::cout << "switching animation " << animationIndex << " " << index << std::endl;
    if (
        index != animationIndex &&
        (animations[animationIndex]->getIsOver() ||
         animations[index]->getPriority() >= animations[animationIndex]->getPriority()))
    {
      animations[animationIndex]->setToInitialState();
      animationIndex = index;
    }
  }

  void switchToDefaultAnimation()
  {
    // se a prioridade >= 100 supercede a animacao default
    // std::cout << "switching to default" << std::endl;
    if (animations[animationIndex]->getIsOver() && animations[animationIndex]->getPriority() >= 100)
    {
      animations[animationIndex]->setToInitialState();
      animationIndex = defaultAnimationIndex;
    }
  }

private:
  Vector2i pos;
  Vector2i size;
  TextureEnum objTexture;
  int animationIndex;
  static const int defaultAnimationIndex = 0;
  std::vector<SpriteAnimation *> animations;
};
