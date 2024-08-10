#pragma once

#include "gameObjectProps.hpp"
#include <iostream>
#include <functional>

inline constexpr int SCREEN_WIDTH = 800;
inline constexpr int SCREEN_HEIGHT = 640;

// TODO VERIFICAR SE N TEM UM LUGAR MELHOR PARA GARDAR ESSES DADOS DE OBJ
inline constexpr int PLAYER_ACCELERATION = 100;

inline void FIREBALL_COLISION()
{
    std::cout << "Fireball collision effect mock" << std::endl;
}
inline constexpr int FIREBALL_ACCELERATION = 200;