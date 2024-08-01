#pragma once

#include "gameObjectProps.hpp"
#include <iostream>
#include <functional>

inline constexpr int SCREEN_WIDTH = 800;
inline constexpr int SCREEN_HEIGHT = 640;

// TODO TRANSFORMAR ESSAS PROPS EM FUNCS QUE ACITAM POSICAO INICIAL OS OUTROS VALORES JA SETADOS
inline constexpr GameObjectProps PLAYER_INFO = {.imagePath = "assets/player.png", .posX = 128, .posY = 128, .width = 32, .height = 32, .rotation = 0.0, .mass = 10};
inline constexpr int PLAYER_ACCELERATION = 100;

inline constexpr GameObjectProps BOX_INFO = {"assets/box.png", 250, 300, 32, 32, 0.1, 10};
inline constexpr GameObjectProps HEAVY_BOX_INFO = {"assets/BoxHeavy.png", 350, 300, 32, 32, 0.1, 100};

inline void FIREBALL_COLISION()
{
    std::cout << "Fireball collision effect mock" << std::endl;
}
inline constexpr int FIREBALL_ACCELERATION = 200;