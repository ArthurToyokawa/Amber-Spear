#include <iostream>

#include "gameObject.hpp"
#include "auraComponent.hpp"

// TODO REFATORAR GAMEOBJECT NO WORLD PARA SHARED_POINTER E SALVA AURAS EM UMA LIST SEPARA AO INVES DE DENTRO DO GAMEOBJECT
AuraComponent::AuraComponent(GameObject *parent, int auraIdentifier, float duration, TextureEnum text, std::function<void(GameObject *)> onStart, std::function<void(GameObject *)> onEndFunc)
{
  if (onStart)
  {
    onStart(parent);
  }
  onEnd = [parent, onEndFunc]()
  { onEndFunc(parent); };

  std::cout << "Aura constructor " << duration << " " << auraIdentifier << std::endl;
  totalTime = duration;
  timeRemaning = duration;
  auraId = auraIdentifier;
  auraTexture = text;
}
AuraComponent::~AuraComponent()
{
  // TODO se o pai for um weak_pointer pode tratar assim
  // onEnd();
  // parent->removeAura(this);
}

void AuraComponent::update(float time)
{
  timeRemaning -= time;
}