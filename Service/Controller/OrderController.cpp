#include "OrderController.h"
#include "../../Data/Repo/OrderRepo.h"

namespace controller {

  //constructor
  OrderController::OrderController(repository::OrderRepo& orderRepo) : orderRepo(orderRepo) {}

  const std::vector<domain::OrderDomain>& OrderController::getOrders() {
    return orderRepo.getOrders();
  }

  std::vector<domain::OrderDomain> OrderController::getOrdersByStatus(domain::OrderStatus status) {
    return orderRepo.getOrdersByStatus(status);
  }

  double OrderController::getTotalOrdersInYear(int year) const {
    return orderRepo.getTotalOrdersInYear(year);
  }

  double OrderController::getTotalOrdersInMonth(int month) const {
    return orderRepo.getTotalOrdersInMonth(month);
  }

  bool OrderController::isOrderNumberUnique(int orderNumber) const {
    return orderRepo.isOrderNumberUnique(orderNumber);
  }

  bool OrderController::canModifyOrder(int orderNumber, const employeedomain::Employee& employee) const {
    return orderRepo.canModifyOrder(orderNumber, employee);
  }

  void OrderController::addOrder(const domain::OrderDomain& order) {
    orderRepo.addOrder(order);
  }

  bool OrderController::updateOrder(int orderNumber, const std::vector<std::pair<Product, int>>& newProducts) {
    return orderRepo.updateOrder(orderNumber, newProducts);
  }

  bool OrderController::setOrderStatus(int orderNumber, domain::OrderStatus newStatus) {
    return orderRepo.setOrderStatus(orderNumber, newStatus);
  }

  bool OrderController::assignEmployeeIfUnassigned(int orderNumber, const employeedomain::Employee& employee) {
    return orderRepo.assignEmployeeIfUnassigned(orderNumber, employee);
  }

  bool OrderController::createReservation(const Customer_Domain::Customer& customer, int orderNumber, const std::vector<std::pair<Product, int>>& products) {
    return orderRepo.createReservation(customer, orderNumber, products);
  }

}