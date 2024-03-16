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
    acc = {10.0, 0.0};
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
    // TODO angulo talvez
    vel[0] += acc[0] * time;
    vel[1] += acc[1] * time;
    pos[0] = pos[0] + (vel[0] * time);
    pos[1] = pos[1] + (vel[1] * time);
    std::cout << "vel [ " << vel[0] << ", " << vel[1] << "]" << std::endl;
    std::cout << "pos [ " << pos[0] << ", " << pos[1] << "]" << std::endl;
  }

private:
  // posicao em metros (x,y)
  std::vector<float> pos;
  // velocidade m/s (x,y)
  std::vector<float> vel;
  // massa em kg
  float pMass;
  // tamanho em metros (x,y)
  std::vector<float> pSize;
  // o quanto a velocidade muda em 1 sec m/s (x,y)
  std::vector<float> acc;
};