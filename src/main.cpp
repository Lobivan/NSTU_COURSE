#include <iostream>

#include "product.hpp"
#include "warehouse.hpp"

int main() {
  char name[] = "fish";
  char category[] = "seafood";
  Product p(name, category, 3, {12, 11, 2023}, 100, 12);
  Warehouse w;
  w.push(p);
  p.set_price(99);
  w.push(p);
  p.set_price(98);
  w.push(p);

  char name1[] = "crab";
  w[0].set_name(name1);

  w.print();
  std::cout << "\n";

  std::ofstream f3("text.dat");
  if (!f3) {
    std::cout << "Ошибка открытия файла";
    return 1;
  }
  w.writeBinary(f3);
  f3.close();

  w.sort();

  w.print();
  std::cout << "\n";

  std::ifstream f4("text.dat");
  if (!f4) {
    std::cout << "Ошибка открытия файла";
    return 1;
  }
  w.readBinary(f4);
  f4.close();

  w.print();
  std::cout << "\n";

  Warehouse::Invoice i;
  int nums[] = {0, 2};
  int counts[] = {2, 1};
  i = w.create_invoice(2, nums, counts);
  i.print();
  std::cout << "\n";
  w.print();
  std::cout << "\n";
  delete[] i.prod_list.products;
  return 0;
}