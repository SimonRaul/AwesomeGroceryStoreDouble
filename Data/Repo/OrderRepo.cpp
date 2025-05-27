#include "../Domain/OrderDomain.h"
#include "../Domain/Product.h"
#include "../Domain/Customer.h"
#include "../Domain/Employee.h"

#include "OrderRepo.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace domain;
using namespace std;

namespace repository {

    std::vector<std::vector<std::string>> OrderRepo::readFileSplitByColon(const std::string& filename) {
        std::vector<std::vector<std::string>> result;
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return result;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> tokens;
            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ':')) {
                tokens.push_back(token);
            }

            result.push_back(tokens);
        }

        file.close();
        return result;
    }

    OrderRepo::OrderRepo(const string& filename) {
    auto lines = readFileSplitByColon(filename);

    for (const auto& tokens : lines) {
        if (tokens.size() < 7) continue;

        int number = stoi(tokens[0]);

        tm date = {};
        istringstream ss_date(tokens[1]);
        ss_date >> get_time(&date, "%Y-%m-%d");
        if (ss_date.fail()) continue;

        OrderStatus status;
        if (tokens[2] == "Reservation") status = OrderStatus::Reservation;
        else if (tokens[2] == "Confirmed") status = OrderStatus::Confirmed;
        else if (tokens[2] == "Completed") status = OrderStatus::Completed;
        else continue;

        vector<pair<Product, int>> products;
        stringstream ss_products(tokens[3]);
        string prod_entry;
        while (getline(ss_products, prod_entry, '|')) {
            stringstream ss_pair(prod_entry);
            string prod_name, qty_str;
            if (getline(ss_pair, prod_name, ',') && getline(ss_pair, qty_str)) {
                int qty = stoi(qty_str);
                Product p(prod_name, 10.0f, 100.0f);
                products.emplace_back(p, qty);
            }
        }

        stringstream ss_customer(tokens[4]);
        string cust_id_str, cust_name, cust_forename, cust_email, cust_pass, cust_address;
        getline(ss_customer, cust_id_str, ',');
        getline(ss_customer, cust_name, ',');
        getline(ss_customer, cust_forename, ',');
        getline(ss_customer, cust_email, ',');
        getline(ss_customer, cust_pass, ',');
        getline(ss_customer, cust_address);
        Customer customer(cust_name, cust_forename, cust_email, cust_pass, cust_address);
        customer.set_id(stoi(cust_id_str));

        stringstream ss_employee(tokens[5]);
        string emp_id_str, emp_name, emp_forename, emp_email, emp_pass, emp_position;
        getline(ss_employee, emp_id_str, ',');
        getline(ss_employee, emp_name, ',');
        getline(ss_employee, emp_forename, ',');
        getline(ss_employee, emp_email, ',');
        getline(ss_employee, emp_pass, ',');
        getline(ss_employee, emp_position);
        employeedomain::Employee employee(emp_name, emp_forename, emp_email, emp_pass, emp_position, {}, 0.0f);
        employee.set_id(stoi(emp_id_str));

        double total_price = stod(tokens[6]);

        OrderDomain order(number, date, status, customer, employee);
        order.setProducts(products);
        order.calculateTotalPrice();

        orders.push_back(order);
    }
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



