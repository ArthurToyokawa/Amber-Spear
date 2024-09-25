#include "textureManager.hpp"
#include "game.hpp"

SDL_Renderer *TextureManager::renderer = nullptr;
SDL_Window *TextureManager::window = nullptr;

TextureManager::TextureManager(const char *title, int xpos, int ypos, int width, int height, int flags)
{
  // iniciando a window
  window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
  if (window)
  {
    std::cout << "window succesful " << std::endl;
  }
  // iniciando o renderer
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (renderer)
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    std::cout << "renderer succesful " << std::endl;
  }
  // carregando as texturas
  std::cout << "loading textures" << std::endl;
  for (int textureIndex = std::to_underlying(TextureEnum::amberSpear);
       textureIndex != std::to_underlying(TextureEnum::COUNT);
       textureIndex++)
  {
    const char *textureLocation = textureEnumUtils->indexToFileLocation(textureIndex);
    std::cout << "index: " << textureIndex << " location: " << textureLocation << std::endl;
    SDL_Surface *tempSurface = IMG_Load(textureLocation);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    textures[textureIndex] = tex;
    SDL_FreeSurface(tempSurface);
  }
  std::cout << "textures loaded succesfully " << std::endl;
}

// TODO REMOVER ESSA FUNC
SDL_Texture *TextureManager::LoadTexture(const char *textureSheet)
{
  SDL_Surface *tempSurface = IMG_Load(textureSheet);
  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_FreeSurface(tempSurface);

  return tex;
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
  SDL_RenderCopy(renderer, tex, &src, &dest);
}
// TODO GUARDAR O PONTEIRO DO ENTITYMANEGER NO TEXTUREMANAGER
void TextureManager::render(EntityManager *eManager, float time)
{
  SDL_RenderClear(renderer);
  // render background
  for (GameObject *obj : eManager->getMap()->getMapObjects())
  {
    renderObject(obj, time);
  }
  // render objects
  renderObject(eManager->getPlayer(), time);
  for (auto &objs : eManager->getObjects())
  {
    renderObject(objs, time);
  }
  for (auto &fb : eManager->getSpells())
  {
    renderObject(fb, time);
  }
  SDL_RenderPresent(renderer);
}

void TextureManager::renderObject(GameObject *obj, float time)
{
  if (obj->getSprite() != nullptr)
  {
    SDL_Texture *objTex = textures[std::to_underlying(obj->getSprite()->getTexture())];
    SDL_Rect srcRect, destRect;
    srcRect.h = obj->getSprite()->getHeight();
    srcRect.w = obj->getSprite()->getWidth();
    srcRect.x = obj->getSprite()->getCurrentAnimation()->getAnimationPosition().x;
    srcRect.y = obj->getSprite()->getCurrentAnimation()->getAnimationPosition().y;
    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
    destRect.x = obj->getSprite()->getX();
    destRect.y = obj->getSprite()->getY();

    SDL_RenderCopy(renderer, objTex, &srcRect, &destRect);
    // lifebar
    if (obj->getLife() != nullptr && obj->getLife()->getShowLifebar())
    {
      SDL_Rect lifeRect;
      lifeRect.h = 2;
      lifeRect.w = obj->getLife()->getLifeBarFill(obj->getSprite()->getWidth());
      lifeRect.x = obj->getSprite()->getX();
      lifeRect.y = obj->getSprite()->getY() - 2;
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
      SDL_RenderFillRect(renderer, &lifeRect);
    }
    // animacao
    obj->getSprite()->getCurrentAnimation()->update(time);
    if (obj->getSprite()->getCurrentAnimation()->getIsOver())
    {
      // std::cout << "animation over switching to default" << std::endl;
      obj->getSprite()->switchToDefaultAnimation();
    }
  }
}