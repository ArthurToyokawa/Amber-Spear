#pragma once

#include <my-lib/math-vector.h>
#include <vector>

class MenuItem;
class MenuText;

using Vector2f = Mylib::Math::Vector<float, 2>;
class MenuItemGenerator
{
public:
  MenuItemGenerator() {}
  MenuItem *makeStart(float posX, float posY);
  MenuItem *makeExit(float posX, float posY);
  MenuItem *makeResume(float posX, float posY);
  MenuItem *makeGoToMain(float posX, float posY);
  MenuItem *makeGoToScoreboard(float posX, float posY);

  MenuText *makeMenuText(float posX, float posY, const char *text);

private:
  static void START_GAME();
  static void EXIT_GAME();
  static void RESUME_GAME();
  static void GO_TO_MAIN();
  static void GO_TO_SCOREBOARD();
};
