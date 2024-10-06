#include <cassert>
#include <iostream>
#include "../src/pointCounter.hpp"

int main()
{
  std::cout << "Contador criado" << std::endl;
  PointCounter *counter = new PointCounter();
  assert(counter != nullptr);
  assert(counter->getPoints() == 0);
  std::cout << "Sucesso" << std::endl;

  std::cout << "Adicionando pontos" << std::endl;
  counter->addPoints(100);
  assert(counter->getPoints() == 100);
  std::cout << "Sucesso" << std::endl;

  std::cout << "O status de mudanca funciona como esperado" << std::endl;
  counter->addPoints(-50);
  assert(counter->pointsChanged());
  assert(counter->getPoints() == 50);
  assert(!counter->pointsChanged());
  std::cout << "Sucesso" << std::endl;
}