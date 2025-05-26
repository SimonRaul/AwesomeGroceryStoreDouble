#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

namespace productdomain {

std::string generateUniqueId();

class Product {
private:
    std::string ID;
    std::string Name;
    float Price;
    float Quantity;

public:
    Product(std::string Name, float Price, float Quantity); //auto generated id
    Product(std::string ID, std::string Name, float Price, float Quantity); //given id

    // Getters
    std::string get_id() const;
    std::string get_name() const;
    float get_price() const;
    float get_quantity() const;

    // Setters
    void set_id(std::string new_id);
    void set_name(std::string new_name);
    void set_price(float new_price);
    void set_quantity(float new_quantity);
};

}

#endif //PRODUCT_H
