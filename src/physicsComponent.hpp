#pragma once
#include <list>
#include <vector>

#include <iostream>

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
      float width)
  {
    pos = {posx, posy};
    pMass = mass;
    vel = {velX, velY};
    pSize = {height, width};
    acc = {0.0, 0.0};
  }
  std::vector<float> getPosition()
  {
    return pos;
  }
  void setAcceleration(float accX, float accY)
  {
    acc = {accX, accY};
  }
  void update(float time)
  {
    if (this->isBreaking(vel[0], acc[0]))
    {
      vel[0] += acc[0] * time * 3;
    }
    else
    {
      vel[0] += acc[0] * time;
    }

    if (this->isBreaking(vel[1], acc[1]))
    {
      vel[1] += acc[1] * time * 3;
    }
    else
    {
      vel[1] += acc[1] * time;
    }
    pos[0] = pos[0] + (vel[0] * time);
    pos[1] = pos[1] + (vel[1] * time);
    std::cout << "vel [ " << vel[0] << ", " << vel[1] << "]" << std::endl;
    std::cout << "pos [ " << pos[0] << ", " << pos[1] << "]" << std::endl;
  }

private:
  // TODO USAR O MATH VECTOR DO MYLIB
  //  posicao em metros (x,y)
  std::vector<float> pos;
  // velocidade m/s (x,y)
  std::vector<float> vel;
  // massa em kg
  float pMass;
  // tamanho em metros (x,y)
  std::vector<float> pSize;
  // o quanto a velocidade muda em 1 sec m/s (x,y)
  std::vector<float> acc;

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