#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "physicsComponent.hpp"
#include <my-lib/math-vector.h>

using Vector2f = Mylib::Math::Vector<float, 2>;

// TODO fazer heranca de physicsComponent e positionComponent
class GameObject
{

public:
    // TODO setar a pos fora do construtor
    GameObject(const char *textureSheet, int startingX, int startingY, int height, int width);

    void updatePhysics(float time);
    void updatePosition();
    void render();
    int getX()
    {
        return xpos;
    }
    int getY()
    {
        return ypos;
    }
    // TODO remover isso
    void moveObject(int x, int y)
    {
        xpos = xpos + x;
        ypos = ypos + y;
    }
    // TODO esse metodo só é necessario para player
    void setAcceleration(float accX, float accY)
    {
        physics.setAcceleration(accX, accY);
    }
    // utilizar gameObject como superclasse para entidades
    // virtual void update() = 0;
    // virtual void render() = 0;

private:
    // TODO posicao em vetor
    int xpos;
    int ypos;

    SDL_Texture *objTexture;
    SDL_Rect srcRect, destRect;

    PhysicsComponent physics;
};