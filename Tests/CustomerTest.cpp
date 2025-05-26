//
// Created by Simon Raul on 5/26/2025.
//

#include <gtest/gtest.h>
#include "../Data/Domain/Customer.h"

using namespace Customer_Domain;

TEST(CustomerTest, ConstructorAndGetters) {
    Customer customer("Popescu", "Ion", "ion.popescu@example.com", "securepass", "Strada Lalelelor 10");

    EXPECT_EQ(customer.get_name(), "Popescu");
    EXPECT_EQ(customer.get_forename(), "Ion");
    EXPECT_EQ(customer.get_email(), "ion.popescu@example.com");
    EXPECT_EQ(customer.get_password(), "securepass");
    EXPECT_EQ(customer.get_address(), "Strada Lalelelor 10");
}

TEST(CustomerTest, SetAddress) {
    Customer customer("Popescu", "Ion", "ion.popescu@example.com", "securepass", "Initial");
    customer.set_address("Noua Adresa 15");

    EXPECT_EQ(customer.get_address(), "Noua Adresa 15");
}

TEST(CustomerTest, SetAndGetId) {
    Customer customer("Popescu", "Ion", "ion.popescu@example.com", "securepass", "Strada Test");
    customer.set_id(42);

    EXPECT_EQ(customer.get_id(), 42);
}
