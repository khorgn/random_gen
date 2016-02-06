#include <iostream>
#include "Generator.hpp"
#include "Strategy.hpp"

using namespace RandomMapEngine;

int main(){
  int sizes[] = {3, 2};
  int dimension = 2;

  Generator p(sizes, dimension);

  p.display();

  return 0;
}
