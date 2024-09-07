#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <my-lib/math-vector.h>
#include <vector>

using Vector2i = Mylib::Math::Vector<int, 2>;

class SpriteAnimation
{
public:
  SpriteAnimation(std::vector<Vector2i> positions, float switchTime, int priority, bool looping);

  void update(float time);
  void setToInitialState();

  Vector2i getAnimationPosition() { return animationPositions[posIndex]; }

  int getPriority() { return animationPriority; }
  bool getIsOver() { return isOver; }

private:
  std::vector<Vector2i> animationPositions;
  std::size_t posIndex;
  float switchAnimationTime;
  float currentTime;
  // se a prioridade >= 100 supercede a animacao default
  int animationPriority;
  bool isLooping;
  bool isOver;
};
