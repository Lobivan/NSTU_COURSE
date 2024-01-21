#include "warehouse.hpp"

#include <cstring>
#include <stdexcept>

Warehouse::Warehouse() {
  head.prev = &head;
  head.next = &head;
}

Warehouse::~Warehouse() { clear(); }

void Warehouse::clear() {
  Warehouse::Node* tmp = head.next;
  Warehouse::Node* tmp1;
  while (tmp != &head) {
    tmp1 = tmp->next;
    delete tmp;
    tmp = tmp1;
  }
  head.next = &head;
  head.prev = &head;
}

int Warehouse::size() {
  int res = 0;
  Warehouse::Node* tmp = &head;
  while (tmp->next != &head) {
    tmp = tmp->next;
    res++;
  }
  return res;
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

void Warehouse::push(Product& prod, int num) {
  if (num < 0 || num >= size()) {
    throw std::out_of_range("index out of range");
  }

  Warehouse::Node* node = new Warehouse::Node;
  node->data = prod;

  Warehouse::Node* tmp = head.next;
  for (int i = 0; i < num; i++) {
    tmp = tmp->next;
  }

  node->prev = tmp->prev;
  node->next = tmp;
  tmp->prev->next = node;
  tmp->prev = node;
}

void Warehouse::pop(int num) {
  if (num < 0 || num >= size()) {
    throw std::out_of_range("index out of range");
  }
  Warehouse::Node* tmp = head.next;
  for (int i = 0; i < num; i++) {
    tmp = tmp->next;
  }
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  delete tmp;
}

void Warehouse::swap_nodes(Warehouse::Node* i, Warehouse::Node* j) {
  Product p;
  p = j->data;
  j->data = i->data;
  i->data = p;
}
void Warehouse::sort() {
  int num = size();
  if (num < 2) return;
  Warehouse::Node* tmp1;
  Warehouse::Node* tmp2;
  for (int i = 0; i < num - 1; i++) {
    tmp1 = head.next;
    tmp2 = tmp1->next;
    for (int j = 0; j < num - 1 - i; j++) {
      if (tmp1->data > tmp2->data) swap_nodes(tmp1, tmp2);
      tmp1 = tmp1->next;
      tmp2 = tmp2->next;
    }
  }
}

Product& Warehouse::operator[](int num) {
  if (num < 0 || num >= size()) {
    throw std::out_of_range("index out of range");
  }
  Warehouse::Node* tmp = head.next;
  for (int i = 0; i < num; i++) {
    tmp = tmp->next;
  }
  return tmp->data;
}

void Warehouse::print() {
  Warehouse::Node* tmp = head.next;
  int i = 1;
  while (tmp != &head) {
    std::cout << i++ << ". ";
    tmp->data.print();
    std::cout << "\n";
    tmp = tmp->next;
  }
}

void Warehouse::writeBinary(std::ofstream& os) {
  int s = size();
  os.write((char*)(&s), sizeof(int));
  Warehouse::Node* tmp = head.next;
  while (tmp != &head) {
    tmp->data.writeBinary(os);
    tmp = tmp->next;
  }
}
void Warehouse::readBinary(std::ifstream& is) {
  clear();
  int s;
  is.read((char*)(&s), sizeof(int));
  Product p;
  for (int i = 0; i < s; i++) {
    p.readBinary(is);
    push(p);
  }
}

Warehouse::Product_list Warehouse::search_name(char* name) {
  Warehouse::Product_list res;
  int s = size();
  res.products = new Product[s];
  res.amount = 0;
  for (int i = 0; i < s; i++) {
    if (strcmp(name, operator[](i).get_name()) == 0) {
      res.products[res.amount++] = operator[](i);
    }
  }
  return res;
}

Warehouse::Product_list Warehouse::search_category(char* category) {
  Warehouse::Product_list res;
  int s = size();
  res.products = new Product[s];
  res.amount = 0;
  for (int i = 0; i < s; i++) {
    if (strcmp(category, operator[](i).get_category()) == 0) {
      res.products[res.amount++] = operator[](i);
    }
  }
  return res;
}

Warehouse::Invoice Warehouse::create_invoice(size_t size, int* prod_nums,
                                             int* prod_count) {
  Warehouse::Invoice res;
  res.prod_list.products = new Product[size];
  res.prod_list.amount = size;
  res.total_price = 0;
  res.total_added_price = 0;
  int s = this->size();
  for (int i = 0; i < size; i++) {
    res.prod_list.products[i] = operator[](prod_nums[i]);
    res.prod_list.products[i].set_count(prod_count[i]);
    operator[](prod_nums[i])
        .set_count(operator[](prod_nums[i]).get_count() - prod_count[i]);
    int sum = res.prod_list.products[i].get_price() * prod_count[i];
    res.total_price += sum;
    res.total_added_price +=
        (double)sum *
        ((double)res.prod_list.products[i].get_added_percent() / (double)100);
  }
  return res;
}