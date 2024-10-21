#pragma once

#include <textureEnumUtils.hpp>
#include <gameObject/gameObject.hpp>
#include <functional>

class AuraSystem
{
public:
  AuraSystem() {}
  void addMassAura(GameObject *target);

private:
  // auras
  const int massAuraId = 1;
  static void addMass(GameObject *target)
  {
    if (target->getPhysics() != nullptr)
    {
      target->getPhysics()->setMass(target->getPhysics()->getMass() + 50.0);
    }
  }
  static void removeMass(GameObject *target)
  {
    if (target->getPhysics() != nullptr)
    {
      target->getPhysics()->setMass(target->getPhysics()->getMass() - 50.0);
    }
  }
};
