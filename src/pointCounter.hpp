#pragma once

class PointCounter
{

public:
  PointCounter()
  {
    points = 0;
    changed = true;
  };
  void addPoints(int toAdd)
  {
    points += toAdd;
    changed = true;
  };
  int getPoints()
  {
    changed = false;
    return points;
  };
  bool pointsChanged() { return changed; };

private:
  int points;
  bool changed;
};