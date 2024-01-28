#include <iostream>

#include "product.hpp"
#include "warehouse.hpp"
#define BUFFLEN 15

char* getstr() {
  char* res = new char[BUFFLEN];
  int reslen = BUFFLEN;
  int ind = 0;
  char c = 'a';
  while (c != '\n') {
    if (ind == reslen) {
      reslen += BUFFLEN;
      char* tmp = new char[reslen];
      for (int i = 0; i < reslen - BUFFLEN; i++) {
        tmp[i] = res[i];
      }
      delete[] res;
      res = tmp;
    }
    std::cin >> std::noskipws >> c;
    res[ind++] = c;
  }
  res[ind - 1] = '\0';
  return res;
}

Product get_pr_from_input() {
  int n;
  Product p;
  std::cout << "Введите наименование товара: ";
  char* str = getstr();
  p.set_name(str);
  delete[] str;
  std::cout << "Введите категорию товара: ";
  str = getstr();
  p.set_category(str);
  delete[] str;
  std::cout << "Введите количество товара: ";
  std::cin >> std::skipws >> n;
  p.set_count(n);
  std::cout << "Введите цену товара: ";
  std::cin >> std::skipws >> n;
  p.set_price(n);
  std::cout << "Введите процент торговой надбавки товара: ";
  std::cin >> std::skipws >> n;
  p.set_added_percent(n);
  int y, m, d;
  std::cout << "Введите год поступления товара: ";
  std::cin >> std::skipws >> y;
  std::cout << "Введите месяц поступления товара(числом): ";
  std::cin >> std::skipws >> m;
  std::cout << "Введите день поступления товара: ";
  std::cin >> std::skipws >> d;
  Product::Date x(d, m, y);
  p.set_date(x);
  return p;
}

void add_product(Warehouse* w) {
  std::cout << "Добавление товара: \n";
  Product p;
  p = get_pr_from_input();
  w->push(p);
  std::cout << "Товар добавлен!\n";
}

void add_product_num(Warehouse* w) {
  std::cout << "Добавление товара по номеру: \n";
  std::cout << "Введите позицию, на которую поместить товар (> 0): ";
  int num;
  std::cin >> num;
  Product p;
  p = get_pr_from_input();
  w->push(p, num - 1);
  std::cout << "Товар добавлен!\n";
}

void remove_product_num(Warehouse* w) {
  std::cout << "Удаление товара по номеру: \n";
  std::cout << "Введите позицию для удаления (> 0): ";
  int num;
  std::cin >> num;
  w->pop(num - 1);
  std::cout << "Товар удалён!\n";
}

void save(Warehouse* w) {
  std::cout << "Сохранение информации о складе в бинарный файл: \n";
  std::cout << "Введите имя файла: ";
  char* name = getstr();
  std::ofstream f3(name);
  if (!f3) {
    std::cout << "Ошибка открытия файла";
    return;
  }
  w->writeBinary(f3);
  f3.close();
  delete[] name;
  std::cout << "Сохранение завершено\n";
  if (!std::cin) {
    char c;
    std::cin >> c;
  }
}

void load(Warehouse* w) {
  std::cout << "Загрузка информации о складе из бинарного файла: \n";
  std::cout << "Введите имя файла: ";
  char* name = getstr();
  std::ifstream f3(name);
  if (!f3) {
    std::cout << "Ошибка открытия файла";
    return;
  }
  w->readBinary(f3);
  f3.close();
  delete[] name;
  std::cout << "Загрузка завершена\n";
}

void count_invoice(Warehouse* w) {
  std::cout << "Составление фактуры: \n";
  std::cout << "Введите номер продукта на складе и необходимое количество\n";
  std::cout << "Для окончания введите -1 -1\n";
  int n = 0;
  int c = 0;
  int* nums = new int[BUFFLEN];
  int* cs = new int[BUFFLEN];
  int amount = 0;
  int size = BUFFLEN;
  std::cin >> std::skipws >> n;
  std::cin >> std::skipws >> c;
  while (n != -1 || c != -1) {
    if (amount == size) {
      int* tmp = new int[size + BUFFLEN];
      for (int i = 0; i < size; i++) tmp[i] = nums[i];
      delete[] nums;
      nums = tmp;
      tmp = new int[size + BUFFLEN];
      for (int i = 0; i < size; i++) tmp[i] = cs[i];
      delete[] cs;
      cs = tmp;
      size += BUFFLEN;
    }
    nums[amount] = n - 1;
    cs[amount++] = c - 1;
    std::cout << n << "+" << c << "\n";
    std::cin.clear();
    std::cin.ignore();
    std::cin >> std::skipws >> n;
    std::cin >> std::skipws >> c;
  }
  for (int i = 0; i < amount; i++) {
    std::cout << nums[i] << " " << cs[i] << "\n";
  }
  Warehouse::Invoice i;
  i = w->create_invoice(amount, nums, cs);
  std::cout << "Фактура составлена:\n";
  i.print();
}

void warehouse_menu() {
  Warehouse w;
  int num = 0;
  char c;
  while (num != 10) {
    std::cout << "\n    Меню управления складом:\n"
              << "1. Посмотреть товары\n"
              << "2. Добавить товар в конец\n"
              << "3. Удалить последний товар\n"
              << "4. Добавить товар по номеру\n"
              << "5. Удалить товар по номеру\n"
              << "6. Отсортировать товары\n"
              << "7. Записать информацию в бинарный файл\n"
              << "8. Загрузить информацию из бинарного файла\n"
              << "9. Составить фактуру\n"
              << "10. Выход\n";
    std::cout << "Введите номер операции: ";
    std::cin >> num;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    switch (num) {
      case 1:
        std::cout << "    Список товаров на складе: \n";
        w.print();
        break;
      case 2:
        add_product(&w);
        break;
      case 3:
        w.pop();
        std::cout << "Товар удалён\n";
        break;
      case 4:
        add_product_num(&w);
        break;
      case 5:
        remove_product_num(&w);
        break;
      case 6:
        w.sort();
        std::cout << "Товары отсортированы!\n";
        break;
      case 7:
        save(&w);
        break;
      case 8:
        load(&w);
        break;
      case 9:
        count_invoice(&w);
        break;
      case 10:
        break;
      default:
        std::cout << num << " - Неверный номер!\n";
        break;
    }
  }
}

int main() {
  warehouse_menu();
  // char name[] = "fish";
  // char category[] = "seafood";
  // Product p(name, category, 3, {12, 11, 2023}, 100, 12);
  // Warehouse w;
  // w.push(p);
  // p.set_price(99);
  // w.push(p);
  // p.set_price(98);
  // w.push(p);

  // char name1[] = "crab";
  // w[0].set_name(name1);

  // w.print();
  // std::cout << "\n";

  // std::ofstream f3("text.dat");
  // if (!f3) {
  //   std::cout << "Ошибка открытия файла";
  //   return 1;
  // }
  // w.writeBinary(f3);
  // f3.close();

  // w.sort();

  // w.print();
  // std::cout << "\n";

  // std::ifstream f4("text.dat");
  // if (!f4) {
  //   std::cout << "Ошибка открытия файла";
  //   return 1;
  // }
  // w.readBinary(f4);
  // f4.close();

  // w.print();
  // std::cout << "\n";

  // Warehouse::Invoice i;
  // int nums[] = {0, 2};
  // int counts[] = {2, 1};
  // i = w.create_invoice(2, nums, counts);
  // i.print();
  // std::cout << "\n";
  // w.print();
  // std::cout << "\n";
  // delete[] i.prod_list.products;
  return 0;
}