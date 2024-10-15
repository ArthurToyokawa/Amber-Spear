#include "physicsComponent.hpp"

using Vector2f = Mylib::Math::Vector<float, 2>;

PhysicsComponent::PhysicsComponent(
    float velX,
    float velY,
    float mass,
    float height,
    float width,
    float friction,
    bool intangible,
    bool unstoppable)
{
  pMass = mass;
  vel.set(velX, velY);
  pSize.set(width, height);
  acc.set(0.0, 0.0);
  pFriction = friction;
  isIntangible = intangible;
  isUnstoppable = unstoppable;
}
Vector2f PhysicsComponent::update(float time, Vector2f pos)
{
  // calculando nova velocidade xy baseado na aceleração
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
  // std::cout << "vel [ " << vel.x << ", " << vel.y << "]" << std::endl;
  //  std::cout << "friction " << pFriction << std::endl;
  //  std::cout << "lost to friction [ " << -vel.x * pFriction << ", " << -vel.y * pFriction << "]" << std::endl;
  // aplicando friccao
  vel.x -= vel.x * pFriction;
  vel.y -= vel.y * pFriction;
  // TODO se a velocidade < x o objeto para por friccao

  // atualiza a posicao
  // pos.x = pos.x + (vel.x * time);
  // pos.y = pos.y + (vel.y * time);
  Vector2f newPos = pos + (vel * time);

  //  std::cout << "ve2 [ " << vel.x << ", " << vel.y << "]" << std::endl;
  // std::cout << "pos [ " << newPos.x << ", " << newPos.y << "]" << std::endl;

  return newPos;
}

bool PhysicsComponent::isBreaking(float velocity, float acceleration)
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
