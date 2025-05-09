
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

namespace Product {

std::string generateUniqueId();

class Product {
public:
  std::string ID;
  std::string Name;
  float Price;
  float Quantity;
  Product(std::string Name, float Price, float Quantity); //auto generated id
  Product(std::string ID, std::string Name, float Price, float Quantity); //given id

};

}

#endif //PRODUCT_H
