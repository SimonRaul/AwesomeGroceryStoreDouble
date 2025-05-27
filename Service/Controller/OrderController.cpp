#include "OrderController.h"
#include "../../Data/Repo/OrderRepo.h"

namespace controller {

  //constructor
  OrderController::OrderController(const std::string& filename, const ProductController& prod_contr) :
  orderRepo(repository::OrderRepo(filename)), productContr(prod_contr) {}

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
    std::vector<std::shared_ptr<Product>> product_list = productContr.listProducts();
    for (auto& product: order.getProducts()) {
      for (int i = 0; i < product_list.size(); i++) {
        if (product.first.get_id() == product_list[i]->get_id()) {
          productContr.updateProduct(product_list[i]->get_id(),
            product_list[i]->get_name(), product_list[i]->get_price(),
            product_list[i]->get_quantity()-product.second);
        }
      }
    }

  }

  bool OrderController::updateOrder(int orderNumber, const std::vector<std::pair<Product, float>>& newProducts) {
    return orderRepo.updateOrder(orderNumber, newProducts);
  }

  bool OrderController::setOrderStatus(int orderNumber, domain::OrderStatus newStatus) {
    return orderRepo.setOrderStatus(orderNumber, newStatus);
  }

  bool OrderController::assignEmployeeIfUnassigned(int orderNumber, const employeedomain::Employee& employee) {
    return orderRepo.assignEmployeeIfUnassigned(orderNumber, employee);
  }

  bool OrderController::createReservation(const Customer_Domain::Customer& customer, const std::vector<std::pair<Product, float>>& products) {
    std::vector<std::shared_ptr<Product>> product_list = productContr.listProducts();
    for (auto& product: products) {
      for (int i = 0; i < product_list.size(); i++) {
        if (product.first.get_id() == product_list[i]->get_id()) {
          productContr.updateProduct(product_list[i]->get_id(),
            product_list[i]->get_name(), product_list[i]->get_price(),
            product_list[i]->get_quantity()-product.second);
        }
      }
    }
    return orderRepo.createReservation(customer, products);
  }


}