//
// Created by Simon Raul on 5/28/2025.
//

#include <gtest/gtest.h>
#include "../Data/Repo/Customer_Repo.h"
#include "../Data/Domain/Customer.h"
#include <memory>

using namespace Customer_Repo;
using namespace Customer_Domain;

class CustomerRepoTest : public ::testing::Test {
protected:
    void SetUp() override {
        repo = std::make_unique<::Customer_Repo::Customer_Repo>("clientsTest.txt");
    }

    std::unique_ptr<::Customer_Repo::Customer_Repo> repo;
};

TEST_F(CustomerRepoTest, LoadInitialCustomersFromFile) {
    auto customers = repo->list();
    ASSERT_EQ(customers.size(), 2);

    EXPECT_EQ(customers[0]->get_name(), "Smith");
    EXPECT_EQ(customers[1]->get_email(), "jane.doe@example.com");
}

TEST_F(CustomerRepoTest, CreateCustomerIncrementsId) {
    auto new_cus = repo->create("Popescu", "Ion", "ion.pop@example.com", "secret", "Str. Nouă");

    ASSERT_NE(new_cus, nullptr);
    EXPECT_EQ(new_cus->get_name(), "Popescu");
    EXPECT_EQ(new_cus->get_address(), "Str. Nouă");

    auto customers = repo->list();
    EXPECT_EQ(customers.size(), 3);  // 2 din fișier + 1 adăugat
}

TEST_F(CustomerRepoTest, CreateWithIdAddsExactId) {
    auto custom = repo->create_with_id(10, "Test", "User", "test.user@example.com", "1234", "Locatie");

    ASSERT_NE(custom, nullptr);
    EXPECT_EQ(custom->get_id(), 10);
    EXPECT_EQ(custom->get_email(), "test.user@example.com");
}

TEST_F(CustomerRepoTest, UpdateCustomerAddress) {
    bool updated = repo->update(1, "New Address 77");

    EXPECT_TRUE(updated);
    auto customers = repo->list();
    EXPECT_EQ(customers[0]->get_address(), "New Address 77");
}

TEST_F(CustomerRepoTest, UpdateNonexistentCustomerFails) {
    EXPECT_FALSE(repo->update(999, "Doesn't Exist"));
}

TEST_F(CustomerRepoTest, RemoveCustomerById) {
    bool removed = repo->remove(2);
    EXPECT_TRUE(removed);

    auto customers = repo->list();
    EXPECT_EQ(customers.size(), 1);
    EXPECT_NE(customers[0]->get_id(), 2);
}

TEST_F(CustomerRepoTest, RemoveNonexistentCustomerFails) {
    EXPECT_FALSE(repo->remove(999));
}

TEST_F(CustomerRepoTest, FindByEmailSuccess) {
    Customer c = repo->find_by_email("john.smith@example.com");
    EXPECT_EQ(c.get_forename(), "John");
}

TEST_F(CustomerRepoTest, FindByEmailThrowsIfNotFound) {
    EXPECT_THROW(repo->find_by_email("not@found.com"), std::runtime_error);
}
