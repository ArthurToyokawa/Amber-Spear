#include <iostream>

#include <gameObject/gameObject.hpp>
#include "lifeComponent.hpp"

LifeComponent::LifeComponent(GameObject *parent, float max, bool show, int pOnDeath)
{
  gameObject = parent;
  maxLife = max;
  currentLife = max;
  showLifebar = show;
  pointsOnDeath = pOnDeath;
};

int LifeComponent::getLifeBarFill(int barWidth)
{
  float lifePct = currentLife / maxLife;
  return (int)(lifePct * barWidth + 0.5);
}

void LifeComponent::dealDamage(float damage)
{
  // reducao de dano
  // true damage
  // outras logicas
  currentLife -= damage;
  if (currentLife <= 0)
  {
    gameObject->kill();
  }
};
void LifeComponent::healDamage(float heal)
{
  // multiplicador de cura
  // overheal
  // outras logicas
  currentLife += heal;
  if (currentLife + heal > maxLife)
  {
    currentLife = maxLife;
  }
  else
  {
    currentLife += heal;
  }
};
