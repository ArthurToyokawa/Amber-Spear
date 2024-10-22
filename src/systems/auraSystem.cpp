#include <iostream>
#include "auraSystem.hpp"

void AuraSystem::addMassAura(GameObject *target)
{
  std::cout << "Adding Aura Blocked" << std::endl;
  if (!target->hasAura(massAuraId))
  {
    target->addAura(massAuraId, 4.0, TextureEnum::goatHead, addMass, removeMass);
  }
}
