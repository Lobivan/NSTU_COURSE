#pragma once

class Product {
 private:
  char* _name;      // наименование товара
  char* _category;  // категория товара
  char* _arrival_date;  // дата поступления в формате гггг.мм.дд
  size_t _count;          // количество
  size_t _price;          // цена
  size_t _added_percent;  // процент торговой надбавки

  char* copy_char_arr(char* arr) const;
  bool date_is_valid(char* date) const;

 public:
  Product();
  Product(char* name, char* category, char* arrival_date, size_t count,
          size_t price, size_t added_percent);
  void print() const;
};