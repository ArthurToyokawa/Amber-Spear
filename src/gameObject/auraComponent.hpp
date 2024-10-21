#pragma once
#include <functional>

class GameObject;

class AuraComponent
{
public:
  AuraComponent(GameObject *parent, int auraId, float duration, TextureEnum text, std::function<void(GameObject *)> onStart, std::function<void(GameObject *)> onEndFunc);
  ~AuraComponent();

  void update(float time);

  int getAuraId() { return auraId; };
  float getTimeRemaining() { return timeRemaning; };
  float getRemainingTimePct() { return timeRemaning / totalTime; };
  TextureEnum getTexture() { return auraTexture; };
  void callOnEnd() { onEnd(); };

private:
  int auraId;
  float totalTime;
  float timeRemaning;
  TextureEnum auraTexture;
  std::function<void()>
      onEnd;
};
