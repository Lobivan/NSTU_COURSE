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
Product::~Product() {
  delete[] _name;
  delete[] _category;
  _name = nullptr;
  _category = nullptr;
}

bool Product::operator==(const Product& other) const {
  if (strcmp(_name, other._name) != 0 ||
      strcmp(_category, other._category) != 0 ||
      _arrival_date != other._arrival_date || _count != other._count ||
      _price != other._price || _added_percent != other._added_percent) {
    return false;
  }
  return true;
}

bool Product::operator<(const Product& other) const {
  if (strcmp(_name, other._name) != 0) strcmp(_name, other._name) < 0;
  if (strcmp(_category, other._category) != 0)
    return strcmp(_category, other._category) < 0;
  if (_price != other._price) _price < other._price;
  if (_count != other._count) _count < other._count;
  if (_arrival_date != other._arrival_date)
    return _arrival_date < other._arrival_date;
  return _added_percent < other._added_percent;
}

bool Product::operator>(const Product& other) const {
  if (strcmp(_name, other._name) != 0) strcmp(_name, other._name) > 0;
  if (strcmp(_category, other._category) != 0)
    return strcmp(_category, other._category) > 0;
  if (_price != other._price) _price > other._price;
  if (_count != other._count) _count > other._count;
  if (_arrival_date != other._arrival_date)
    return _arrival_date > other._arrival_date;
  return _added_percent > other._added_percent;
}

Product& Product::operator=(const Product& other) {
  delete[] _name;
  _name = copy_char_arr(other._name);
  delete[] _category;
  _category = copy_char_arr(other._category);
  _count = other._count;
  _arrival_date = other._arrival_date;
  _price = other._price;
  _added_percent = other._added_percent;
  return *this;
}

const char* const Product::get_name() const { return _name; }
const char* const Product::get_category() const { return _category; }
size_t Product::get_count() const { return _count; }
Product::Date Product::get_date() const { return _arrival_date; }
size_t Product::get_price() const { return _price; }
size_t Product::get_added_percent() const { return _added_percent; }

void Product::set_name(char* name) {
  delete[] _name;
  _name = copy_char_arr(name);
}
void Product::set_category(char* category) {
  delete[] _category;
  _category = copy_char_arr(category);
}
void Product::set_count(size_t count) { _count = count; }
void Product::set_date(Product::Date& date) { _arrival_date = date; }
void Product::set_price(size_t price) { _price = price; }
void Product::set_added_percent(size_t added_percent) {
  _added_percent = added_percent;
}

void Product::print() {
  std::cout << "Наименование: " << _name << "; категория: " << _category
            << "; количество: " << _count
            << "; дата поступления: " << _arrival_date << "; цена: " << _price
            << "; процент торговой надбавки:" << _added_percent;
}