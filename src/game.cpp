#include "common.hpp"
#include "game.hpp"
#include "textureManager.hpp"
#include "gameObject.hpp"
#include "map.hpp"
#include "keyboardHandler.hpp"

#include "./ECS/ECS.hpp"
#include "./ECS/components.hpp"

#include <list>

Map *map;
// TODO UMA CLASSE PLAYER COM MOVIMENTOS
GameObject *player;
// TODO transformar isso em um array de objetos
std::list<GameObject *> fireballs;

SDL_Renderer *Game::renderer = nullptr;

KeyboardHandler *kHandler;
// TODO usar o timer do jogo pra isso
int testFbLimiter = 0;
// Manager manager;
// auto &newPlayer(manager.addEntity());

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
  map = new Map();
  player = new GameObject("assets/player.png", 0, 0);
  kHandler = new KeyboardHandler(player);
  // newPlayer.addComponent<PositionComponent>();
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
      kHandler->handleKeyPress(event.key.keysym.sym);
      break;
    case SDL_KEYUP:
      kHandler->handleKeyRelease(event.key.keysym.sym);
      break;
    default:
      break;
    }
  }
}

void Game::update()
{
  // TODO lidar com o movimento em uma classe diferente tratando separado movimento e outras keys
  for (auto key : kHandler->getActiveKeys())
  {
    switch (key)
    {
    case SDLK_UP:
      player->moveObject(0, -5);
      break;
    case SDLK_DOWN:
      player->moveObject(0, +5);
      break;
    case SDLK_LEFT:
      player->moveObject(-5, 0);
      break;
    case SDLK_RIGHT:
      player->moveObject(+5, 0);
      break;
    case SDLK_q:
    {
      // creating fireball
      if (testFbLimiter == 0)
      {
        GameObject *fb = new GameObject("assets/fireball.png", player->getX() + 32, player->getY());
        fireballs.push_back(fb);
        testFbLimiter = 10;
      }
      break;
    }
    case SDLK_ESCAPE:
      isRunning = false;
      break;
    default:
      break;
    }
  }
  // TODO lidando com o comportamento de fireballs, mudar isso para outra classe
  for (auto it = fireballs.begin(); it != fireballs.end();)
  {
    auto &fb = *it;
    // std::cout << fb->getX() << " ";
    fb->moveObject(10, 0);
    if (fb->getX() > SCREEN_WIDTH || fb->getY() > SCREEN_HEIGHT)
    {
      delete fb;
      it = fireballs.erase(it);
    }
    else
    {
      fb->update();
      ++it;
    }
  }
  // std::cout << std::endl;
  if (testFbLimiter != 0)
  {
    testFbLimiter--;
  }
  player->update();
  //  manager.update();
  //  std::cout << newPlayer.getComponent<PositionComponent>().x() << "," << newPlayer.getComponent<PositionComponent>().y() << std::endl;
}

void Game::render()
{
  SDL_RenderClear(renderer);
  // render background
  map->DrawMap();
  // render objects
  player->render();
  // TODO lidando com o comportamento de fireballs, mudar isso para outra classe
  for (auto &fb : fireballs)
  {
    fb->render();
  }
  SDL_RenderPresent(renderer);
}

void Game::clean()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  std::cout << "ending game" << std::endl;
}