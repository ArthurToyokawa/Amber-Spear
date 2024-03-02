#pragma once
#include "game.hpp"

class Map
{
public:
  Map();
  ~Map();

  void LoadMap(int arr[20][25]);
  void DrawMap();

private:
  SDL_Rect src, dest;
  SDL_Texture *rock;
  SDL_Texture *lava;
  SDL_Texture *error;

  int map[20][25];
};