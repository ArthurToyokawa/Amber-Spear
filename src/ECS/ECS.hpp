#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentId = std::size_t;

inline ComponentId getComponentTypeId()
{
  static ComponentId lastID = 0;
  return lastID++;
}

template <typename T>
ComponentId getComponentTypeId() noexcept
{
  static ComponentId typeID = getComponentTypeId();
  return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component
{
public:
  // owner reference
  Entity *entity;

  virtual void init() {}
  virtual void update() {}
  virtual void draw() {}
  virtual ~Component() {}
};

class Entity
{
private:
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitSet;

public:
  void update()
  {
    for (auto &c : components)
    {
      c->update();
    }
  }
  void draw()
  {
    for (auto &c : components)
    {
      c->draw();
    }
  }
  bool isActive() { return active; }
  void destroy() { active = false; }

  template <typename T>
  bool hasComponent() const
  {
    return componentBitSet(getComponentTypeId<T>());
  }

  template <typename T, typename... TArgs>
  T &addComponent(TArgs &&...mArgs)
  {
    T *c(new T(std::forward<TArgs>(mArgs)...));
    c->entity = this;
    std::unique_ptr<Component> uptr{c};
    components.emplace_back(std::move(uptr));

    componentArray[getComponentTypeId<T>()] = c;
    componentBitSet[getComponentTypeId<T>()] = true;

    c->init();
    return *c;
  }

  template <typename T>
  T &getComponent() const
  {
    auto ptr(componentArray[getComponentTypeId<T>()]);
    return *static_cast<T *>(ptr);
  }
  // example of use
  //  gameObject.getComponent<positionComponent>().setXpos(25);
};

class Manager
{
private:
  std::vector<std::unique_ptr<Entity>> entities;

public:
  void update()
  {
    for (auto &e : entities)
    {
      e->update();
    }
  }
  void draw()
  {
    for (auto &e : entities)
    {
      e->draw();
    }
  }
  void refresh()
  {
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity> &mEntity)
                                  {
                                    return !mEntity->isActive();
                                  }),
                   std::end(entities));
  }

  Entity &addEntity()
  {
    Entity *entity = new Entity();
    std::unique_ptr<Entity> uptr{entity};
    entities.emplace_back(std::move(uptr));
    return *entity;
  }
};