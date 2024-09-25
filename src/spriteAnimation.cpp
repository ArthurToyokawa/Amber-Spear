#include "spriteAnimation.hpp"

#include <iostream>

SpriteAnimation::SpriteAnimation(std::vector<Vector2i> positions, float switchTime, int priority, bool looping)
{
  isLooping = looping;
  animationPositions = positions;
  switchAnimationTime = switchTime;
  animationPriority = priority;
  setToInitialState();
  if (!isLooping)
  {
    // std::cout << "starting non looping animation" << std::endl;
  }
};

void SpriteAnimation::setToInitialState()
{
  posIndex = 0;
  currentTime = 0;
  isOver = false;
}

void SpriteAnimation::update(float time)
{
  if (animationPositions.size() == 1 && isLooping)
  {
    return;
  }
  // std::cout << "non looping animation" << posIndex << std::endl;
  currentTime += time;
  if (currentTime >= switchAnimationTime)
  {
    currentTime -= switchAnimationTime;
    if (posIndex + 1 == animationPositions.size())
    {
      if (!isLooping && animationPositions.size() == 1)
      {
        // std::cout << "setting animation over" << std::endl;
        isOver = true;
      }
      // std::cout << "switching to animation 0 " << " x " << animationPositions[posIndex].x << " y " << animationPositions[posIndex].y << std::endl;
      posIndex = 0;
    }
    else
    {
      posIndex += 1;
      // std::cout << "switching to animation " << posIndex << " x " << animationPositions[posIndex].x << " y " << animationPositions[posIndex].y << std::endl;
    }
  }
};
