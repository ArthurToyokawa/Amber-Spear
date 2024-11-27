#pragma once

#include "score.hpp"
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class FileManager
{
public:
  FileManager() {}

  std::list<Score *> readFile()
  {
    std::list<Score *> scores;
    std::ifstream inFile(fileName);

    if (!inFile.is_open())
    {
      std::cerr << "Error: Could not open file for reading.\n";
      return scores;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
      std::istringstream iss(line);
      std::string user;
      int scoreValue;

      if (iss >> user >> scoreValue)
      {
        char *userChar = new char[user.size() + 1];
        strcpy(userChar, user.c_str());
        scores.push_back(new Score(userChar, scoreValue));
      }
    }

    inFile.close();
    return scores;
  }

  void writeFile(const std::list<Score *> &newScores)
  {
    std::ofstream outFile(fileName, std::ios::trunc);

    if (!outFile.is_open())
    {
      std::cerr << "Error: Could not open file for writing.\n";
      return;
    }

    for (const auto &score : newScores)
    {
      outFile << score->getUser() << " " << score->getScoreValue() << "\n";
    }

    outFile.close();
  }

private:
  std::string fileName = "scores.txt";
};
