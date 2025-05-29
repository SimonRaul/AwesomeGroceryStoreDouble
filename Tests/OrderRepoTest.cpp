//
// Created by Simon Raul on 5/29/2025.
//

#include <gtest/gtest.h>
#include "../Data/Repo/OrderRepo.h"
#include "../Data/Domain/Product.h"
#include "../Data/Domain/Customer.h"
#include "../Data/Domain/Employee.h"

using namespace repository;
using namespace domain;
using namespace Customer_Domain;
using namespace employeedomain;
using namespace std;

class OrderRepoTest : public ::testing::Test {
protected:
    std::string test_filename = "orders_test.txt";
    std::unique_ptr<OrderRepo> repo;

    void SetUp() override {
        repo = std::make_unique<OrderRepo>(test_filename);
    }
};

TEST_F(OrderRepoTest, LoadOrdersFromFile) {
    const auto& orders = repo->getOrders();
    ASSERT_EQ(orders.size(), 2);
    EXPECT_EQ(orders[0].getNumber(), 1);
    EXPECT_EQ(orders[1].getStatus(), OrderStatus::Confirmed);
    EXPECT_EQ(orders[0].getCustomer().get_email(), "john.doe@example.com");
}

TEST_F(OrderRepoTest, GetOrderProducts) {
    auto products = repo->get_order_products(1);
    ASSERT_EQ(products.size(), 2);
    EXPECT_EQ(products[0].first.get_name(), "Apple");
    EXPECT_EQ(products[0].second, 2);
}

TEST_F(OrderRepoTest, GetOrdersByStatus) {
    auto reservations = repo->getOrdersByStatus(OrderStatus::Reservation);
    EXPECT_EQ(reservations.size(), 1);
    EXPECT_EQ(reservations[0].getNumber(), 1);
}

TEST_F(OrderRepoTest, GetTotalOrdersInYear) {
    double total = repo->getTotalOrdersInYear(2025);
    EXPECT_DOUBLE_EQ(total, 80.00);
}

TEST_F(OrderRepoTest, GetTotalOrdersInMonth) {
    double april_total = repo->getTotalOrdersInMonth(4);
    EXPECT_DOUBLE_EQ(april_total, 50.00);

    double march_total = repo->getTotalOrdersInMonth(3);
    EXPECT_DOUBLE_EQ(march_total, 30.00);
}

TEST_F(OrderRepoTest, IsOrderNumberUniqueWorks) {
    EXPECT_FALSE(repo->isOrderNumberUnique(1));
    EXPECT_TRUE(repo->isOrderNumberUnique(999));
}

TEST_F(OrderRepoTest, CanModifyOrderChecksStatusAndEmployee) {
    Employee jane("Smith", "Jane", "jane.smith@example.com", "admin123", "Manager", {}, 0.0f);
    jane.set_id(201);

    EXPECT_TRUE(repo->canModifyOrder(1, jane));
    EXPECT_FALSE(repo->canModifyOrder(2, jane));  // Confirmed by someone else
}

TEST_F(OrderRepoTest, SetOrderStatusUpdatesCorrectly) {
    EXPECT_TRUE(repo->setOrderStatus(1, OrderStatus::Confirmed));
    auto updated = repo->getOrdersByStatus(OrderStatus::Confirmed);
    EXPECT_EQ(updated.size(), 2);
}

TEST_F(OrderRepoTest, UpdateOrderReplacesProductList) {
    std::vector<std::pair<Product, float>> new_prods = {
        {Product("Orange", 5.0f, 20.0f), 4}
    };
    EXPECT_TRUE(repo->updateOrder(1, new_prods));
    auto products = repo->get_order_products(1);
    EXPECT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].first.get_name(), "Orange");
    EXPECT_EQ(products[0].second, 4);
}

TEST_F(OrderRepoTest, AssignEmployeeIfUnassignedWorks) {
    Customer dummy("x", "y", "z@a.com", "pass", "addr");
    dummy.set_id(500);
    std::vector<std::pair<Product, float>> prods = {
        {Product("Book", 10.0f, 100.0f), 1}
    };

    repo->createReservation(dummy, prods);  // employee.id = 0

    Employee emp("Emp", "A", "a@a.com", "pw", "Worker", {}, 0.0f);
    emp.set_id(999);

    auto latest_id = repo->getOrders().back().getNumber();
    EXPECT_TRUE(repo->assignEmployeeIfUnassigned(latest_id, emp));
}

TEST_F(OrderRepoTest, CreateReservationAddsNewOrder) {
    Customer new_c("Test", "Client", "test@t.com", "pass", "addr");
    new_c.set_id(700);
    std::vector<std::pair<Product, float>> list = {
        {Product("Milk", 5.0f, 10.0f), 2}
    };

    EXPECT_TRUE(repo->createReservation(new_c, list));
    auto orders = repo->getOrders();
    auto& last = orders.back();
    EXPECT_EQ(last.getCustomer().get_id(), 700);
    EXPECT_EQ(last.getProducts().size(), 1);
}
