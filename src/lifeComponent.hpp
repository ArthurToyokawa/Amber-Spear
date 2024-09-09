#pragma once

class GameObject;

class LifeComponent
{
public:
  LifeComponent(GameObject *parent, float maxLife, bool showLifebar);

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

  GameObject *gameObject;
};
