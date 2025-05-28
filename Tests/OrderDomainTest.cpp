//
// Created by Simon Raul on 5/26/2025.
//

#include <gtest/gtest.h>
#include "../Data/Domain/OrderDomain.h"
#include "../Data/Domain/Product.h"
#include "../Data/Domain/Employee.h"
#include "../Data/Domain/Customer.h"

using namespace domain;
using namespace productdomain;
using namespace employeedomain;
using namespace Customer_Domain;

// Helper pentru creare dată
std::tm make_date(int year, int month, int day) {
    std::tm t{};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    return t;
}

// Helper pentru Customer
Customer make_customer() {
    Customer c("Doe", "John", "john.doe@example.com", "pass123", "Main Street 1");
    c.set_id(1);
    return c;
}

// Helper pentru Employee
Employee make_employee() {
    year_month_day birthday{year{1990}, month{1}, day{1}};
    Employee e("Smith", "Anna", "anna.smith@example.com", "emp456", "Cashier", birthday, 3000.0f);
    e.set_id(101);
    return e;
}

TEST(OrderDomainTest, ConstructorInitializesFields) {
    Customer c = make_customer();
    Employee e = make_employee();
    std::tm date = make_date(2024, 12, 15);

    OrderDomain order(1001, date, OrderStatus::Confirmed, c, e);

    EXPECT_EQ(order.getNumber(), 1001);
    EXPECT_EQ(order.getDate().tm_year, date.tm_year);
    EXPECT_EQ(order.getStatus(), OrderStatus::Confirmed);
    EXPECT_EQ(order.getEmployee().get_email(), "anna.smith@example.com");
    EXPECT_EQ(order.getTotalPrice(), 0.0);
    EXPECT_TRUE(order.getProducts().empty());
}

TEST(OrderDomainTest, ChangeStatusWorks) {
    OrderDomain order(1, make_date(2024, 1, 1), OrderStatus::Reservation, make_customer(), make_employee());
    order.changeStatus(OrderStatus::Completed);

    EXPECT_EQ(order.getStatus(), OrderStatus::Completed);
}

TEST(OrderDomainTest, ChangeOrderAndCalculatePrice) {
    Product p1("Milk", 5.0f, 1.0f);
    Product p2("Bread", 3.0f, 1.0f);
    std::vector<std::pair<Product, float>> items = {
        {p1, 2},  // 2 * 5 = 10
        {p2, 3}   // 3 * 3 = 9
    };

    OrderDomain order(2, make_date(2024, 1, 1), OrderStatus::Confirmed, make_customer(), make_employee());
    order.changeOrder(items);

    EXPECT_EQ(order.getProducts().size(), 2);
    EXPECT_DOUBLE_EQ(order.getTotalPrice(), 19.0);
}

TEST(OrderDomainTest, CreateReservationWorksCorrectly) {
    Product p("Juice", 4.5f, 1.0f);
    std::vector<std::pair<Product, float>> list = {{p, 4}}; // 4 * 4.5 = 18.0

    Customer customer = make_customer();
    OrderDomain order(3, make_date(2024, 1, 1), OrderStatus::Completed, customer, make_employee());
    order.createReservation(customer, list);

    EXPECT_EQ(order.getStatus(), OrderStatus::Reservation);
    EXPECT_DOUBLE_EQ(order.getTotalPrice(), 18.0);

    Employee default_emp; // C-tor implicit
    EXPECT_EQ(order.getEmployee().get_email(), default_emp.get_email());
}

TEST(OrderDomainTest, SettersWorkIndependently) {
    OrderDomain order(4, make_date(2024, 1, 1), OrderStatus::Reservation, make_customer(), make_employee());

    // Test setStatus
    order.setStatus(OrderStatus::Confirmed);
    EXPECT_EQ(order.getStatus(), OrderStatus::Confirmed);

    // Test setProducts
    Product p("Apple", 2.0f, 1.0f);
    std::vector<std::pair<Product, float>> prods = {{p, 5}};
    order.setProducts(prods);
    EXPECT_EQ(order.getProducts().size(), 1);

    // Test setEmployee
    year_month_day birthday{year{1985}, month{6}, day{15}};
    Employee newEmp("Pop", "Ion", "ion.pop@grocery.com", "pw", "Manager", birthday, 3500.0f);
    newEmp.set_id(202);
    order.setEmployee(newEmp);
    EXPECT_EQ(order.getEmployee().get_name(), "Pop");
}


