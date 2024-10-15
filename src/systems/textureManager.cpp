#include <iomanip>
#include <sstream>

#include <gameObject/gameObject.hpp>
#include <game.hpp>
#include <common.hpp>
#include <globals.hpp>
#include "textureManager.hpp"

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
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
void TextureManager::render(float time)
{
  SDL_RenderClear(renderer);
  // render background
  for (GameObject *obj : gWorld.getMapObjects())
  {
    renderObject(obj, time);
  }
  // render objects
  renderObject(gWorld.getPlayer(), time);
  for (auto &objs : gWorld.getObjects())
  {
    renderObject(objs, time);
  }
  for (auto &fb : gWorld.getSpells())
  {
    renderObject(fb, time);
  }
  // render point counter
  renderPointCounter();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

void TextureManager::renderPointCounter()
{
  if (gPointCounter.pointsChanged())
  {
    if (message != nullptr)
    {
      std::cout << "destroy message " << message << std::endl;

      SDL_DestroyTexture(message);
      message = nullptr;
    }
    std::cout << "pointsChanged" << std::endl;

    TTF_Font *Sans = TTF_OpenFont("OpenSans-Regular.ttf", 24);
    SDL_Color White = {255, 255, 255};

    std::ostringstream oss;
    oss << std::setw(6) << std::setfill('0') << gPointCounter.getPoints();
    std::string pointsText = oss.str();

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, pointsText.c_str(), White);
    message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = surfaceMessage->w;
    Message_rect.h = surfaceMessage->h;

    SDL_FreeSurface(surfaceMessage);
  }
  SDL_RenderCopy(renderer, message, NULL, &Message_rect);
}
