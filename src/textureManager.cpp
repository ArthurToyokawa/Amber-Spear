#include "textureManager.hpp"

// TODO guardar texturas e reutilizar elas
SDL_Texture *TextureManager::LoadTexture(const char *textureSheet)
{
  SDL_Surface *tempSurface = IMG_Load(textureSheet);
  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return tex;
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
  SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}