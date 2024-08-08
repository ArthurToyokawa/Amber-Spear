#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <my-lib/math-vector.h>

using Vector2i = Mylib::Math::Vector<int, 2>;
using Vector2f = Mylib::Math::Vector<float, 2>;

class SpriteComponent
{
public:
  SpriteComponent(const char *textureSheet, int startingX, int startingY, int height, int width);

  void update(Vector2f physPos);
  void render();
  int getX() { return pos.x; }
  int getY() { return pos.y; }
  int getHeight() { return srcRect.h; }
  int getWidth() { return srcRect.w; }

private:
  Vector2i pos;
  SDL_Texture *objTexture;
  SDL_Rect srcRect, destRect;
};
