#include "warehouse.hpp"

Warehouse::Warehouse() {
  head.prev = &head;
  head.next = &head;
}

Warehouse::~Warehouse() {
  Warehouse::Node* tmp = head.next;
  while (tmp != &head) {
    Warehouse::Node* tmp1 = tmp->next;
    delete tmp;
    tmp = tmp1;
  }
}

void Warehouse::push(Product& prod) {
  Warehouse::Node* node = new Warehouse::Node;
  node->data = prod;
  node->prev = head.prev;
  node->next = &head;
  head.prev->next = node;
  head.prev = node;
}

void Warehouse::pop() {
  if (head.prev != &head) {
    Warehouse::Node* tmp = head.prev;
    head.prev = tmp->prev;
    tmp->prev->next = &head;
    delete tmp;
  }
}