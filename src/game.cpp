
#include "game.hpp"
#include "textureManager.hpp"
#include "keyboardHandler.hpp"
#include "game.hpp"
#include "entityManager.hpp"
#include "gameObjectGenerator.hpp"
#include "mapManager.hpp"
#include "globals.hpp"

#include <list>

EntityManager *eManager;
MapManager *mapManager;
GameObjectGenerator *gameObjectGenerator;

KeyboardHandler *kHandler;

const int FPS = 20;
const int frameDelay = 1000 / FPS;

Game::Game() {};
Game::~Game() {};

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = 0;

  if (fullscreen)
  {
    flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    if (TTF_Init() == -1)
    {
      std::cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
      isRunning = false;
    }
    std::cout << "init succesful " << std::endl;
    textureManager = new TextureManager(title, xpos, ypos, width, height, flags);
    isRunning = true;
  }
  else
  {
    isRunning = false;
  }
  kHandler = new KeyboardHandler();

  initializeGlobals();

  gameObjectGenerator = new GameObjectGenerator();
  mapManager = new MapManager(gameObjectGenerator);
  eManager = new EntityManager(gameObjectGenerator);
  this->gameLoop();
}

void Game::gameLoop()
{
  Uint32 frameStart;
  Uint32 lastUpdateTick = 0;
  float SecsBetweenUpdate;
  int frameTime;

  std::cout << "frameDelay: " << frameDelay << std::endl;

  while (this->running())
  {

    frameStart = SDL_GetTicks();

    this->handleEvents();
    // TODO DESCOMENTAR
    //  std::cout << "time since last update: " << SDL_GetTicks() - lastUpdateTick << std::endl;
    SecsBetweenUpdate = (SDL_GetTicks() - lastUpdateTick) / 1000.0;
    this->update(SecsBetweenUpdate);
    lastUpdateTick = SDL_GetTicks();

    this->render(SecsBetweenUpdate);
    // tempo requirido para realizar os eventos
    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay >= frameTime)
    {
      SDL_Delay(frameDelay - frameTime);
    }
    else
    {
      /*TODO TRATAR LAG */
    }
    frameTime = SDL_GetTicks() - frameStart;
  }

  this->clean();
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

void Game::update(float time)
{
  for (auto key : kHandler->getActiveKeys())
  {
    switch (key)
    {
    case SDLK_ESCAPE:
      isRunning = false;
      break;
    default:
      break;
    }
  }
  eManager->handleKeys(kHandler->getActiveKeys());
  eManager->update(time);
}

void Game::render(float time)
{
  textureManager->render(time);
}

void Game::clean()
{
  textureManager->destroy();
  SDL_Quit();
  std::cout << "ending game" << std::endl;
}