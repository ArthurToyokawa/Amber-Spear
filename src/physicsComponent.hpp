#pragma once
#include <list>
#include <vector>

#include <iostream>
#include <my-lib/math-vector.h>

using Vector2f = Mylib::Math::Vector<float, 2>;

class PhysicsComponent
{
public:
  PhysicsComponent(
      float posx,
      float posy,
      float velX,
      float velY,
      float mass,
      float height,
      float width,
      float friction);

  float getMass()
  {
    return pMass;
  }
  Vector2f getSize()
  {
    return pSize;
  }
  Vector2f getPosition()
  {
    return pos;
  }
  void setPosition(float posX, float posY)
  {
    pos.set(posX, posY);
  }
  Vector2f getAcceleration()
  {
    return acc;
  }
  void setAcceleration(float accX, float accY)
  {
    acc.set(accX, accY);
  }
  Vector2f getVelocity()
  {
    return vel;
  }
  void setVelocity(float velX, float velY)
  {
    vel.set(velX, velY);
  }
  void update(float time);

private:
  //  posicao em metros (x,y)
  Vector2f pos;
  // velocidade m/s (x,y)
  Vector2f vel;
  // massa em kg
  float pMass;
  // tamanho em metros (x,y)
  Vector2f pSize;
  // o quanto a velocidade muda em 1 sec m/s (x,y)
  Vector2f acc;
  // porcentagem de velocidade perdida por segundo
  float pFriction;

  bool isBreaking(float velocity, float acceleration);
};