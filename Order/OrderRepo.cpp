#include "../Order/OrderDomain.h"
#include "../Product/Domain/Product.h"
#include "../Customer/Domain/Customer.h"
#include "../Employee/Domain/Employee.h"

#include "OrderRepo.h"

#include <iostream>
#include <vector>

using namespace domain;

namespace repository {

    OrderRepo::OrderRepo(std::vector<domain::OrderDomain> orders) {
      this->orders = orders;
    }

    const std::vector<domain::OrderDomain>& OrderRepo::getOrders() {
        return orders;
    }

    std::vector<domain::OrderDomain> OrderRepo::getOrdersByStatus(domain::OrderStatus status) {
        std::vector<domain::OrderDomain> result;
        for (const auto& order : orders) {
            if (order.getStatus() == status) {
                result.push_back(order);
            }
        }
        return result;
    }

    double OrderRepo::getTotalOrdersInYear(int year) const {
        int count = 0;
        for (const auto& order : orders) {
            if ((order.getDate().tm_year + 1900) == year) {
                ++count;
            }
        }
        return static_cast<double>(count);
    }

    double OrderRepo::getTotalOrdersInMonth(int month) const {
        int count = 0;
        for (const auto& order : orders) {
            if ((order.getDate().tm_mon + 1) == month) {
                ++count;
            }
        }
        return static_cast<double>(count);
    }

    bool OrderRepo::isOrderNumberUnique(int orderNumber) const {
        for (const auto& order : orders) {
            if (order.getNumber() == orderNumber) {
                return false;
            }
        }
        return true;
    }

    bool OrderRepo::canModifyOrder(int orderNumber, const employeedomain::Employee& employee) const {
        for (const auto& order : orders) {
            if (order.getNumber() == orderNumber) {
                if (order.getStatus() == domain::OrderStatus::Completed) {
                    return false;
                }
                if (order.getEmployee().get_id() == employee.get_id()) {
                    return true;
                } else {
                    return false;
                }
            }
        }
        return false; // order not found
    }

    void OrderRepo::addOrder(const OrderDomain& order) {
        if (!isOrderNumberUnique(order.getNumber())) {
            std::cerr << "Order number already exists.\n";
            return;
        }
        orders.push_back(order);
    }

    bool OrderRepo::updateOrder(int orderNumber, const std::vector<std::pair<Product, int>>& newProducts) {
        for (auto& order : orders) {
            if (order.getNumber() == orderNumber) {
                if (order.getStatus() == OrderStatus::Completed) {
                    std::cerr << "Cannot modify an order that's Completed\n";
                    return false;
                }
                if (newProducts.empty()) {
                    std::cerr << "Product list cannot be empty.\n";
                    return false;
                }

                order.setProducts(newProducts);
                order.calculateTotalPrice();
                return true;
            }
        }
        std::cerr << "Order number not found.\n";
        return false;
    }

    bool OrderRepo::setOrderStatus(int orderNumber, OrderStatus newStatus) {
        for (auto& order : orders) {
            if (order.getNumber() == orderNumber) {
                if (order.getStatus() == OrderStatus::Completed) {
                    std::cerr << "Cannot change the status of a Completed order\n";
                    return false;
                }
                order.setStatus(newStatus);
                return true;
            }
        }
        std::cerr <<"Order number not found.\n";
        return false;
    }

    bool OrderRepo::assignEmployeeIfUnassigned(int orderNumber, const employeedomain::Employee& employee) {
        for (auto& order : orders) {
            if (order.getNumber() == orderNumber) {
                if (order.getEmployee().get_id() == 0) {                        //id=0 means that the order isn't assigned to anybody
                    order.setEmployee(employee);
                    return true;
                } else {
                    std::cerr << "Order already has an assigned employee.\n";
                    return false;
                }
            }
        }
        std::cerr << "Order number not found.\n";
        return false;
    }

    bool OrderRepo::createReservation(const Customer_Domain::Customer& customer, int orderNumber,
        const std::vector<std::pair<Product, int>>& products) {

        if (!isOrderNumberUnique(orderNumber)) {
            std::cerr << "Order number already exists.\n";
            return false;
        }

        if (products.empty()) {
            std::cerr << "Cannot create reservation with empty product list.\n";
            return false;
        }

        std::tm now = {};
        OrderDomain newOrder(orderNumber, now, OrderStatus::Reservation, customer, employeedomain::Employee());
        newOrder.setProducts(products);
        newOrder.calculateTotalPrice();

        orders.push_back(newOrder);
        return true;
    }

}



