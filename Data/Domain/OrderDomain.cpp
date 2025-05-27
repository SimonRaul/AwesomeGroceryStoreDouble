#include "OrderDomain.h"

#include "Product.h"
#include "../../Data/Domain/Customer.h"
#include "Employee.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace Customer_Domain;

namespace domain {

OrderDomain::OrderDomain(int number, std::tm date, OrderStatus status, Customer customer, employeedomain::Employee employee) {
        this->number = number;
        this->date = date;
        this->status = status;
        this->customer = customer;
        this->employee = employee;
        this->totalprice = 0.0;
}

int OrderDomain::getNumber() const {
  return this->number;
}

std::tm OrderDomain::getDate() const {
  return this->date;
}

OrderStatus OrderDomain::getStatus() const {
  return this->status;
}

std::vector<std::pair<Product, float>> OrderDomain::getProducts() const {
  return this->products;
}

double OrderDomain::getTotalPrice() const {
  return this->totalprice;
}

employeedomain::Employee OrderDomain::getEmployee() const {
  return this->employee;
}

void OrderDomain::setStatus(OrderStatus newstatus) {
  this->status = newstatus;
}

void OrderDomain::setEmployee(const employeedomain::Employee& newemployee) {
  this->employee = newemployee;
}

void OrderDomain::setProducts(const std::vector<std::pair<Product, float>>& newproducts) {
    this->products = newproducts;
}

void OrderDomain::changeStatus(OrderStatus newstatus) {
  setStatus(newstatus);
}

void OrderDomain::changeOrder(const std::vector<std::pair<Product, float>>& newProducts) {
  setProducts(newProducts);
  calculateTotalPrice();
}

void OrderDomain::calculateTotalPrice() {
	totalprice = 0.0;
    for (const auto& item : products) {
        const Product& product = item.first;
        int quantity = item.second;
        totalprice += product.get_price() * quantity;
    }
}

void OrderDomain::createReservation(const Customer& customer, const std::vector<std::pair<Product, float>>& products) {
	this->customer = customer;
    this->products = products;
    this->status = OrderStatus::Reservation;

    this->employee = employeedomain::Employee();
    calculateTotalPrice();
}

Customer OrderDomain::getCustomer() const
{
  return this->customer;
}

}