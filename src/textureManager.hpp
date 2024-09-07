#pragma once

// #include "map.hpp"
#include "entityManager.hpp"
#include "textureEnumUtils.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// TODO SEPARAR EM 2 CLASSES SCREEN E TEXTUREMANAGER
class TextureManager
{

public:
  TextureManager(const char *title, int xpos, int ypos, int width, int height, int flags);
  static SDL_Texture *LoadTexture(const char *textureSheet);
  static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
  void render(EntityManager *eManager, float time);
  void renderObject(GameObject *obj, float time);
  void destroy()
  {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
  };

private:
  static SDL_Renderer *renderer;
  static SDL_Window *window;
  TextureEnumUtils *textureEnumUtils;

  // TODO USAR STD::ARRAY
  SDL_Texture *textures[22];
};