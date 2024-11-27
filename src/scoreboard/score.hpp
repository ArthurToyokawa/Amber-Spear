#pragma once

class Score
{
public:
  Score(const char *u, int val)
  {
    user = u;
    scoreValue = val;
  }
  const char *getUser()
  {
    return user;
  }

  int getScoreValue()
  {
    return scoreValue;
  }

  // std::string getScoreString()
  // {
  //   return std::string(user) + " " + std::to_string(scoreValue);
  // }

  char *getScoreString()
  {
    // Create a string representation first
    std::string scoreStr = std::string(user) + " " + std::to_string(scoreValue);

    // Allocate new memory and copy the string
    char *result = new char[scoreStr.length() + 1];
    strcpy(result, scoreStr.c_str());

    return result;
  }

private:
  const char *user;
  int scoreValue;
};
