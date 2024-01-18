#include "product.hpp"

#include <cstring>
#include <iostream>

char* Product::copy_char_arr(char* arr) const {
  size_t len = strlen(arr) + 1;
  char* res = new char[len];
  for (int i = 0; i < len; i++) {
    res[i] = arr[i];
  }
  return res;
}

bool Product::date_is_valid(char* date) const {
  //
}

Product::Product()
    : _name(nullptr),
      _category(nullptr),
      _arrival_date(nullptr),
      _count(0),
      _price(0),
      _added_percent(0) {}
Product::Product(char* name, char* category, char* arrival_date, size_t count,
                 size_t price, size_t added_percent) {
  _name = copy_char_arr(name);
  _category = copy_char_arr(category);
}
void Product::print() const { std::cout << "I am product\n"; }