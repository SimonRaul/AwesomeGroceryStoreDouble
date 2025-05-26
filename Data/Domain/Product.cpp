#include "Product.h"

namespace productdomain {

  std::string generateUniqueId() {
    static unsigned long counter = 0;
    ++counter;
    return std::to_string(counter);
  }

  Product::Product(std::string ID, std::string Name, float Price, float Quantity) {
    this->ID = ID;
    this->Name = Name;
    this->Price = Price;
    this->Quantity = Quantity;
  }

  Product::Product(std::string Name, float Price, float Quantity) {
    this->ID = generateUniqueId();
    this->Name = Name;
    this->Price = Price;
    this->Quantity = Quantity;
  }

  // Getters implementation
  std::string Product::get_id() const {
    return ID;
  }

  std::string Product::get_name() const {
    return Name;
  }

  float Product::get_price() const {
    return Price;
  }

  float Product::get_quantity() const {
    return Quantity;
  }

  // Setters implementation
  void Product::set_id(std::string new_id) {
    ID = new_id;
  }

  void Product::set_name(std::string new_name) {
    Name = new_name;
  }

  void Product::set_price(float new_price) {
    Price = new_price;
  }

  void Product::set_quantity(float new_quantity) {
    Quantity = new_quantity;
  }
}