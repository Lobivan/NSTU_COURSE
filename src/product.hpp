#pragma once

#include <fstream>
#include <iostream>
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
    int get_year() const { return _year; }
    int get_month() const { return _month; }
    int get_day() const { return _day; }
    void set_year(int year) { _year = year; }
    void set_month(int month) {
      _month = month;
      if (!is_valid()) throw std::invalid_argument("incorrect month!");
    }
    void set_day(int day) {
      _day = day;
      if (!is_valid()) throw std::invalid_argument("incorrect day!");
    }
    Date& operator=(const Date& other) {
      _year = other._year;
      _month = other._month;
      _day = other._day;
      return *this;
    }
    bool operator<(const Date& other) const {
      if (_year != other._year) return _year < other._year;
      if (_month != other._month) return _month < other._month;
      return _day < other._day;
    }
    bool operator>(const Date& other) const {
      if (_year != other._year) return _year > other._year;
      if (_month != other._month) return _month > other._month;
      return _day > other._day;
    }
    bool operator==(const Date& other) const {
      return _year == other._year && _month == other._month &&
             _day == other._day;
    }
    bool operator!=(const Date& other) const { return !operator==(other); }

    friend std::ostream& operator<<(std::ostream& stream, Date& date) {
      stream << date._day << "." << date._month << "." << date._year;
      return stream;
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
  ~Product();

  bool operator==(const Product& other) const;
  bool operator<(const Product& other) const;
  bool operator>(const Product& other) const;
  Product& operator=(const Product& other);

  const char* const get_name() const;
  const char* const get_category() const;
  size_t get_count() const;
  Date get_date() const;
  size_t get_price() const;
  size_t get_added_percent() const;

  void set_name(char* name);
  void set_category(char* category);
  void set_count(size_t count);
  void set_date(Date& date);
  void set_price(size_t price);
  void set_added_percent(size_t added_percent);

  void print();

  void writeBinary(std::ofstream& os);
  void readBinary(std::ifstream& is);
};