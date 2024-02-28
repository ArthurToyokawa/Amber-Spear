#include "game.hpp"

SDL_Texture *playerTex;
SDL_Rect srcRect, destRect;

Game::Game(){};
Game::~Game(){};

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = 0;

  if (fullscreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
  }
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    std::cout << "init succesful " << std::endl;
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window)
    {
      std::cout << "window succesful " << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer)
    {
      SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
      std::cout << "renderer succesful " << std::endl;
    }
    isRunning = true;
  }
  else
  {
    isRunning = false;
  }
  // player img
  SDL_Surface *tmpSurface = IMG_Load("assets/player.png");
  playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
  SDL_FreeSurface(tmpSurface);
}

void Game::handleEvents()
{
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0)
  {
    switch (event.type)
    {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
      {
      case SDLK_UP:
        counterY = counterY - 10;
        break;
      case SDLK_DOWN:
        counterY = counterY + 10;
        break;
      case SDLK_LEFT:
        counterX = counterX - 10;
        break;
      case SDLK_RIGHT:
        counterX = counterX + 10;
        break;
      }
      break;
    // case SDL_MOUSEBUTTONUP:
    //   isRunning = false;
    //   break;
    default:
      break;
    }
  }
}

void Game::update()
{
  // if (counterX == 768)
  // {
  //   horizontal = false;
  // }
  // else if (counterX == 0)
  // {
  //   horizontal = true;
  // }
  // if (horizontal)
  // {
  //   counterX++;
  // }
  // else
  // {
  //   counterX--;
  // }
  // if (counterY == 568)
  // {
  //   vertical = false;
  // }
  // else if (counterY == 0)
  // {
  //   vertical = true;
  // }
  // if (vertical)
  // {
  //   counterY++;
  // }
  // else
  // {
  //   counterY--;
  // }
  destRect.h = 32;
  destRect.w = 32;
  destRect.x = counterX;
  destRect.y = counterY;
  std::cout << "X: " << counterX << " Y: " << counterY << std::endl;
}

void Game::render()
{
  SDL_RenderClear(renderer);
  // render background
  // render objects
  //  1 null renders entire image 2 null render on the entire frame
  SDL_RenderCopy(renderer, playerTex, NULL, &destRect);
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "ending game" << std::endl;
}