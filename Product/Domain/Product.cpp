#include "Product.h"


namespace Product {

  std::string generateUniqueId() {
    static unsigned long counter = 0;
    ++counter;
    return std::to_string(counter);
  }

  Product::Product(std::string ID, std::string Name, float Price, float Quantity) {
    this -> ID = ID;
    this -> Name = Name;
    this -> Price = Price;
    this -> Quantity = Quantity;
  }

  Product::Product (std::string Name, float Price, float Quantity) {
    this -> ID = generateUniqueId();
    this -> Name = Name;
    this -> Price = Price;
    this -> Quantity = Quantity;
  }



}