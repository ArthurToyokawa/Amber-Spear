#pragma once
#include <list>
#include <vector>

#include <iostream>
#include <my-lib/math-vector.h>

using Vector2f = Mylib::Math::Vector<float, 2>;

class PhysicsComponent
{
public:
  void initPhysics(
      float posx,
      float posy,
      float velX,
      float velY,
      float mass,
      float height,
      float width,
      float friction
      )
  {
    pos.set(posx, posy);
    pMass = mass;
    vel.set(velX, velY);
    pSize.set(height, width);
    acc.set(0.0, 0.0);
    pFriction = friction;
  }
  Vector2f getPosition()
  {
    return pos;
  }
  void setAcceleration(float accX, float accY)
  {
    acc.set(accX, accY);
  }
  void update(float time)
  {
    //calculando nova velocidade xy baseado na aceleração
    if (this->isBreaking(vel.x, acc.x))
    {
      vel.x += acc.x * time * 2;
    }
    else
    {
      vel.x += acc.x * time;
    }

    if (this->isBreaking(vel.y, acc.y))
    {
      vel.y += acc.y * time * 2;
    }
    else
    {
      vel.y += acc.y * time;
    }
    std::cout << "vel [ " << vel.x << ", " << vel.y << "]" << std::endl;
    std::cout << "friction " << pFriction << std::endl;
    std::cout << "lost to friction [ " << -vel.x * pFriction << ", " << -vel.y * pFriction << "]" << std::endl;
    //aplicando friccao
    vel.x -= vel.x * pFriction;
    vel.y -= vel.y * pFriction;
    //TODO se a velocidade < x o objeto para por friccao

    //atualiza a posicao
    pos.x = pos.x + (vel.x * time);
    pos.y = pos.y + (vel.y * time);

    std::cout << "ve2 [ " << vel.x << ", " << vel.y << "]" << std::endl;
    std::cout << "pos [ " << pos.x << ", " << pos.y << "]" << std::endl;
  }

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


  bool isBreaking(float velocity, float acceleration)
  {
    if ((velocity == 0 || acceleration == 0))
    {
      return false;
    }
    if (velocity > 0)
    {
      if (acceleration < 0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      if (acceleration > 0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
};