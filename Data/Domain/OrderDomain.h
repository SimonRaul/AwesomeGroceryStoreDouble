#ifndef ORDERDOMAIN_H
#define ORDERDOMAIN_H

#include "Product.h"
#include "../../Data/Domain/Customer.h"
#include "Employee.h"

#include <string>
#include <ctime>
#include <vector>

using namespace Customer_Domain;
using namespace productdomain;

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
    std::vector<std::pair<Product, float>> products;
    Customer customer;
    employeedomain::Employee employee;
    double totalprice;

  public:
    OrderDomain(int number, std::tm date, OrderStatus status, Customer customer, employeedomain::Employee employee);

    //getter methods
    int getNumber() const;

    const std::tm getDate() const;
    OrderStatus getStatus() const;
    std::vector<std::pair<Product, float>> getProducts() const;

    std::string products_to_string(std::vector<std::pair<Product, float>>);

    double getTotalPrice() const;
    employeedomain::Employee getEmployee() const;
    Customer getCustomer() const;

    //setter methods
    //setter method for changing status between Reservation, Confirmed and Completed
    void setStatus(OrderStatus newstatus);

    //setter method for assigning an employee to an order (only if the order doesn't already have an assigned employee)
    void setEmployee(const employeedomain::Employee& newemployee);

    //setter method for changing the list of products
    void setProducts(const std::vector<std::pair<Product, float>>& newproducts);


    //methods for employee
    //changes status between Reservation, Confirmed and Completed (unless the original status is "Completed")
    void changeStatus(OrderStatus newStatus);

    //changes the list of products to a new list
    void changeOrder(const std::vector<std::pair<Product, float>>& newProducts);

    //calculates the total price
    void calculateTotalPrice();

    //creates a "Reservation" order, that doesn't have an assigned employee
    void createReservation(const Customer& customer, const std::vector<std::pair<Product, float>>& products);

    static std::string status_to_string(OrderStatus status) {
        switch (status) {
            case OrderStatus::Reservation: return "Reservation";
            case OrderStatus::Confirmed:   return "Confirmed";
            case OrderStatus::Completed:   return "Completed";
            default: return "Unknown";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const OrderDomain& order) {
        // OrderStatus order_status = order.getStatus();
        const std::tm tm = order.getDate();
        os << "ID: " << order.getNumber() << ", "
           << "Date: " <<  std::asctime(&tm)
           // << "Status: " << order.status_to_string(order_status) << ", "
           << "Total Price: " << order.getTotalPrice() << "\n";
        return os;
    }


};

}

#endif //ORDERDOMAIN_H
