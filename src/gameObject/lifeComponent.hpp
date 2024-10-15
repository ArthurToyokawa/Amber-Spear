#pragma once

#include <globals.hpp>

class GameObject;

class LifeComponent
{
public:
  LifeComponent(GameObject *parent, float maxLife, bool showLifebar, int pOnDeath);
  ~LifeComponent()
  {
    if (pointsOnDeath != 0)
    {
      gPointCounter.addPoints(pointsOnDeath);
    }
  }

  void update(float time);

  float getCurrentLife() { return currentLife; }
  float getMaxLife() { return maxLife; }
  bool getShowLifebar() { return showLifebar; }

  int getLifeBarFill(int barWidth);

  void dealDamage(float damage);
  void healDamage(float heal);

private:
  float maxLife;
  float currentLife;
  bool showLifebar;
  int pointsOnDeath = 0;

  GameObject *gameObject;
};
