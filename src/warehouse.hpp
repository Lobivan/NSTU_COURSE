#pragma once

#include <fstream>

#include "product.hpp"

class Warehouse {
 private:
  // Узел в списке
  class Node {
   public:
    Node* prev;
    Product data;
    Node* next;
    Node() : prev(nullptr), next(nullptr) {}
  };

  // Головной узел, пустой
  Node head;

  // Метод обмена двух узлов
  void swap_nodes(Node* i, Node* j);

 public:
  Warehouse();
  ~Warehouse();

  // Очистка списка
  void clear();

  // Количество элементов в списке
  int size();

  void push(Product& prod);
  void pop();
  void push(Product& prod, int num);
  void pop(int num);

  void sort();

  Product& operator[](int num);

  void print();

  void writeBinary(std::ofstream& os);
  void readBinary(std::ifstream& is);

  // Структура, хранящая несколько продуктов
  struct Product_list {
    Product* products;  // Продукты в списке
    size_t amount;  // Количество продуктов в списке
    void print() {
      for (int i = 0; i < amount; i++) {
        products[i].print();
        std::cout << "\n";
      }
    }
  };

  // Поиск по имени и категории
  Product_list search_name(char* name);
  Product_list search_category(char* category);

  // Фактура
  struct Invoice {
   public:
    Product_list prod_list;    // Список товаров в фактуре
    int total_price;           // Сумма цен товаров
    double total_added_price;  // Сумма торговой надбавки
    void print() {
      std::cout << "общая сумма: " << total_price
                << "\n сумма торговой надбавки: " << total_added_price << "\n";
      prod_list.print();
    }
  };

  // Создание фактуры
  Invoice create_invoice(size_t size, int* prod_nums, int* prod_count);
};