#include <iostream>

#include "product.hpp"

int main() {
  char name[] = "fish";
  char category[] = "seafood";
  Product p(name, category, 3, {12, 11, 2023}, 100, 12);
  p.print();
  return 0;
}