#pragma once

#include "gameObjectProps.hpp"
#include <iostream>
#include <functional>

inline constexpr int SCREEN_WIDTH = 800;
inline constexpr int SCREEN_HEIGHT = 640;

inline constexpr GameObjectProps PLAYER_INFO = {"assets/player.png", 128, 128, 32, 32, 0.0};

inline constexpr int PLAYER_ACCELERATION = 100;

inline constexpr GameObjectProps BOX_INFO = {"assets/box.png", 300, 300, 32, 32, 0.1};

inline void FIREBALL_COLISION()
{
    std::cout << "Fireball collision effect occured" << std::endl;
}