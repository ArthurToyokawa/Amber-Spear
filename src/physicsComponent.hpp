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
      float velX,
      float velY,
      float mass,
      float height,
      float width,
      float friction,
      bool intangible, // TODO VERIFICAR SE ISSO É NECESSARIO OU SE INTANGIVEL == SPELL
      bool Unstoppable);

  float getMass() { return pMass; }
  Vector2f getSize() { return pSize; }
  bool getIsIntangible() { return isIntangible; }
  bool getIsUnstoppable() { return isUnstoppable; }

  Vector2f getAcceleration() { return acc; }
  void setAcceleration(float accX, float accY)
  {
    if (!isUnstoppable)
    {
      acc.set(accX, accY);
    }
  }
  Vector2f getVelocity() { return vel; }
  void setVelocity(float velX, float velY)
  {
    if (!isUnstoppable)
    {
      vel.set(velX, velY);
    }
  }
  void applyForce(int forceX, int forceY)
  {
    if (!isUnstoppable)
    {
      // aplicando a forca por 1 segundo setando a velocidade
      vel.set(forceX / pMass, forceY / pMass);
    }
  };
  Vector2f update(float time, Vector2f pos);

private:
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
  // se um objeto bloqueia ou n outro objeto em colisão
  bool isIntangible;
  // se pula a logica de colisao ou outras mudancas de valocidade/acc
  bool isUnstoppable;

  bool isBreaking(float velocity, float acceleration);
};