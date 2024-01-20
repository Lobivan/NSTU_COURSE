#pragma once

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

 public:
  Warehouse();
  ~Warehouse();
  void push(Product& prod);
  void pop();
};