#pragma once

#include <fstream>

#include "product.hpp"

class Warehouse {
 private:
  class Node {
   public:
    Node* prev;
    Product data;
    Node* next;
    Node() : prev(nullptr), next(nullptr) {}
  };

  Node head;

  void swap_nodes(Node* i, Node* j);

 public:
  Warehouse();
  ~Warehouse();

  void clear();

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

  struct Product_list {
    Product* products;
    size_t amount;
    void print() {
      for (int i = 0; i < amount; i++) {
        products[i].print();
        std::cout << "\n";
      }
    }
  };

  Product_list search_name(char* name);
  Product_list search_category(char* category);

  struct Invoice {
   public:
    Product_list prod_list;
    int total_price;
    double total_added_price;
    void print() {
      std::cout << "общая сумма: " << total_price
                << "\n сумма торговой надбавки: " << total_added_price << "\n";
      prod_list.print();
    }
  };

  Invoice create_invoice(size_t size, int* prod_nums, int* prod_count);
};