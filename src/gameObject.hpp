#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "physicsComponent.hpp"
#include "spellComponent.hpp"
#include "gameObjectProps.hpp"
#include <my-lib/math-vector.h>
#include <functional> // for std::function

using Vector2i = Mylib::Math::Vector<int, 2>;

// TODO fazer heranca de physicsComponent e positionComponent
class GameObject
{

public:
    // TODO setar a pos fora do construtor
    GameObject(const char *textureSheet, int startingX, int startingY, int height, int width, float friction);
    GameObject(const GameObjectProps &props);

    // TODO OPERADORES PRA EQUALS
    // bool operator == (const GameObject& g) const { return pos.x == g.getX() && pos.y == g.getY(); }
    // bool operator != (const GameObject& g) const { return !operator==(g); }

    void updatePhysics(float time);
    void updatePosition();
    void render();
    int getX()
    {
        return pos.x;
    }
    int getY()
    {
        return pos.y;
    }
    int getHeight()
    {
        return srcRect.h;
    }
    int getWidth()
    {
        return srcRect.w;
    }
    bool isAlive()
    {
        return alive;
    }
    bool isDead()
    {
        return !alive;
    }
    void kill()
    {
        if (spell != nullptr)
        {
            delete spell;
        }
        alive = false;
    }
    // Metodos de physics
    void moveObject(int x, int y)
    {
        pos.set(pos.x + x, pos.y + y);
    }
    void setAcceleration(float accX, float accY)
    {
        physics.setAcceleration(accX, accY);
    }
    void setVelocity(float velX, float velY)
    {
        physics.setVelocity(velX, velY);
    }
    // Metodos de spells
    void setSpell(std::function<void()> onCastFunc, std::function<void()> onCollisionFunc)
    {
        spell = new SpellComponent(onCastFunc, onCollisionFunc);
    }
    SpellComponent *getSpell()
    {
        return spell;
    }
    // utilizar gameObject como superclasse para entidades
    // virtual void update() = 0;
    // virtual void render() = 0;

private:
    void initialize(const char *textureSheet, int startingX, int startingY, int height, int width, float friction);

    Vector2i pos;
    bool alive;

    SDL_Texture *objTexture;
    SDL_Rect srcRect, destRect;

    // TODO TRANSFORM PHISYCS EM UM APONTADOR *
    PhysicsComponent physics;
    SpellComponent *spell = nullptr;
};