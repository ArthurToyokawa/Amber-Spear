#pragma once

#include "game.hpp"

// TODO modifica essa classe para ficar dentro de obj e manter a textura
class TextureManager
{

public:
  static SDL_Texture *LoadTexture(const char *textureSheet);
  static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
};