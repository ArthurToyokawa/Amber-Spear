#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "textureEnumUtils.hpp"

#include <my-lib/math-vector.h>

using Vector2i = Mylib::Math::Vector<int, 2>;
using Vector2f = Mylib::Math::Vector<float, 2>;

class SpriteComponent
{
public:
  SpriteComponent(TextureEnum texture, int startingX, int startingY, int height, int width);

  void update(Vector2f physPos);
  int getX() { return pos.x; }
  int getY() { return pos.y; }
  int getWidth() { return size.x; }
  int getHeight() { return size.y; }
  TextureEnum getTexture() { return objTexture; }

private:
  Vector2i pos;
  Vector2i size;
  TextureEnum objTexture;
};
