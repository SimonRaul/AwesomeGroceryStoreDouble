#ifndef ORDERREPO_H
#define ORDERREPO_H

#include "../Domain/OrderDomain.h"
#include "../Domain/Product.h"
#include "../Domain/Customer.h"
#include "../Domain/Employee.h"

#include <iostream>
#include <vector>
#include <fstream>

namespace repository {

class OrderRepo {
  private:
  std::vector<domain::OrderDomain> orders;

  public:
  OrderRepo(const std::string& filename);

  std::vector<std::vector<std::string>> readFileSplitByColon(const std::string& filename);

  const std::vector<domain::OrderDomain>& getOrders();

  //returns all the orders with a specified status
  std::vector<domain::OrderDomain> getOrdersByStatus(domain::OrderStatus status);

  //calculates the number of orders in a specified year
  double getTotalOrdersInYear(int year) const;

  //calculates the number of orders in a specified month
  double getTotalOrdersInMonth(int month) const;

  //checks if the order number is unique
  bool isOrderNumberUnique(int orderNumber) const;

  //checks if an employee can modify an order
  bool canModifyOrder(int orderNumber, const employeedomain::Employee& employee) const;

  //adds a new order
  void addOrder(const domain::OrderDomain& order);

  //Updates the list of products in an order
  bool updateOrder(int orderNumber, const std::vector<std::pair<Product, int>>& newProducts);

  //Changes the status of an order (unless it's already "Completed")
  bool setOrderStatus(int orderNumber, domain::OrderStatus newStatus);

  //Assigns an employee to an order (unless the order is already assigned to someone)
  bool assignEmployeeIfUnassigned(int orderNumber, const employeedomain::Employee& employee);

  //creates a reservation
  bool createReservation(const Customer_Domain::Customer& customer, const std::vector<std::pair<Product, int>>& products);   //change ordderNumber logic

};

}

#endif //ORDERREPO_H
