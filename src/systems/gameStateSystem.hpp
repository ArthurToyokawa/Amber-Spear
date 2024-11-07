#pragma once

class GameStateSystem
{

public:
  GameStateSystem() {};

  bool isRunning() { return running; };
  void stopRunning() { running = false; };

private:
  bool running = true;
};