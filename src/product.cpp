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

Product::Product()
    : _name(nullptr),
      _category(nullptr),
      _arrival_date({1, 1, 1}),
      _count(0),
      _price(0),
      _added_percent(0) {}
Product::Product(char* name, char* category, size_t count, Date arrival_date,
                 size_t price, size_t added_percent)
    : _count(count),
      _arrival_date(arrival_date),
      _price(price),
      _added_percent(added_percent) {
  _name = copy_char_arr(name);
  _category = copy_char_arr(category);
  if (!_arrival_date.is_valid()) throw std::invalid_argument("incorrect date!");
}
void Product::print() const {
  std::cout << "Наименование: " << _name << " ;категория: " << _category
            << " ;количество: " << _count << " ;дата поступления: "
            << " ;цена: "
            << " ;процент торговой надбавки:";
}