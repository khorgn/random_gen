#include <iostream>
#include "Generator.hpp"
#include "Strategy.hpp"

int main(){
  int sizes[] = {3, 2};
  int dimension = 2;

  PerlinNoise p(sizes, dimension);

  p.display();

  return 0;
}
