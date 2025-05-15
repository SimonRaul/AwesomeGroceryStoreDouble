#ifndef ORDERDOMAIN_H
#define ORDERDOMAIN_H

#include "../Product/Domain/Product.h"
#include "../Customer/Domain/Customer.h"
#include "../Employee/Domain/Employee.h"

#include <string>
#include <ctime>
#include <vector>

using namespace Customer_Domain;

namespace domain {

enum class OrderStatus {
    Reservation,
    Confirmed,
    Completed
};

class OrderDomain {
  private:
    int number;
    std::tm date;
    OrderStatus status;
    std::vector<std::pair<Product::Product, int>> products;
    Customer customer;
    employeedomain::Employee employee;
    double totalprice;

  public:
    OrderDomain(int number, std::tm date, OrderStatus status, Customer customer, employeedomain::Employee employee);

    //getter methods
    int getNumber() const;
    std::tm getDate() const;
    OrderStatus getStatus() const;
    std::vector<std::pair<Product::Product, int>> getProducts() const;
    double getTotalPrice() const;
    employeedomain::Employee getEmployee() const;

    //setter methods
    //setter method for changing status between Reservation, Confirmed and Completed
    void setStatus(OrderStatus newstatus);

    //setter method for assigning an employee to an order (only if the order doesn't already have an assigned employee)
    void setEmployee(const employeedomain::Employee& newemployee);

    //setter method for changing the list of products
    void setProducts(const std::vector<std::pair<Product::Product, int>>& newproducts);


    //methods for employee
    //changes status between Reservation, Confirmed and Completed (unless the original status is "Completed")
    void changeStatus(OrderStatus newStatus);

    //changes the list of products to a new list
    void changeOrder(const std::vector<std::pair<Product::Product, int>>& newProducts);

    //calculates the total price
    void calculateTotalPrice();

    //creates an "Reservation" order, that doesn't have an assigned employee
    void createReservation(const Customer& customer, const std::vector<std::pair<Product::Product, int>>& products);


};

}

#endif //ORDERDOMAIN_H
