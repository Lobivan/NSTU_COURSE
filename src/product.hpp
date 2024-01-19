#pragma once

#include <stdexcept>

class Product {
 public:
  class Date {
   private:
    int _year;
    int _month;
    int _day;

   public:
    bool is_valid() {
      if (_month < 1 || _day < 1 || _month > 12 || _day > 31) return false;
      return true;
    }
    Date() : _day(1), _month(1), _year(1){};
    Date(int day, int month, int year) : _day(day), _month(month), _year(year) {
      if (!is_valid()) throw std::invalid_argument("incorrect date!");
    };
    int get_year() { return _year; }
    int get_month() { return _month; }
    int get_day() { return _day; }
    void set_year(int year) { _year = year; }
    void set_month(int month) {
      _month = month;
      if (!is_valid()) throw std::invalid_argument("incorrect month!");
    }
    void set_day(int day) {
      _day = day;
      if (!is_valid()) throw std::invalid_argument("incorrect day!");
    }
  };

 private:
  char* _name;            // наименование товара
  char* _category;        // категория товара
  size_t _count;          // количество
  Date _arrival_date;     // дата поступления
  size_t _price;          // цена
  size_t _added_percent;  // процент торговой надбавки

  char* copy_char_arr(char* arr) const;

 public:
  Product();
  Product(char* name, char* category, size_t count, Date arrival_date,
          size_t price, size_t added_percent);
  void print() const;
};