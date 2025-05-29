//
// Created by Simon Raul on 5/28/2025.
//

#include <gtest/gtest.h>
#include "../Data/Repo/ProductRepository.h"
#include "../Data/Domain/Product.h"
#include <fstream>

using namespace productrepo;
using namespace productdomain;

class ProductRepositoryTest : public ::testing::Test {
protected:
    std::string test_filename = "prod_test.txt";

    void SetUp() override {
        // Resetăm fișierul cu conținutul inițial pentru fiecare test
        std::ofstream file(test_filename);
        file << "1:Apple iPhone 15:999.99:12\n";
        file << "2:Samsung Galaxy S24:899.5:20\n";
        file.close();

        repo = std::make_unique<ProductRepository>(test_filename);
    }

    std::unique_ptr<ProductRepository> repo;
};

TEST_F(ProductRepositoryTest, LoadInitialProducts) {
    auto products = repo->list();
    ASSERT_EQ(products.size(), 2);

    EXPECT_EQ(products[0]->get_id(), "1");
    EXPECT_EQ(products[1]->get_name(), "Samsung Galaxy S24");
    EXPECT_FLOAT_EQ(products[1]->get_quantity(), 20.0f);
}

TEST_F(ProductRepositoryTest, CreateProductAddsNew) {
    auto new_product = repo->create("Google Pixel 8", 799.99f, 10.0f);
    EXPECT_NE(new_product, nullptr);
    EXPECT_EQ(new_product->get_name(), "Google Pixel 8");

    auto products = repo->list();
    EXPECT_EQ(products.size(), 3);
}

TEST_F(ProductRepositoryTest, CreateWithIdAddsCorrectly) {
    auto new_product = repo->create_with_id("10", "MacBook Air", 1200.0f, 5.0f);
    EXPECT_EQ(new_product->get_id(), "10");
    EXPECT_EQ(new_product->get_quantity(), 5.0f);
}

TEST_F(ProductRepositoryTest, UpdateProductWorks) {
    bool updated = repo->update("1", "iPhone 15 Pro", 1099.99f, 8.0f);
    EXPECT_TRUE(updated);

    auto products = repo->list();
    auto& p = products[0];
    EXPECT_EQ(p->get_name(), "iPhone 15 Pro");
    EXPECT_FLOAT_EQ(p->get_price(), 1099.99f);
    EXPECT_FLOAT_EQ(p->get_quantity(), 8.0f);
}

TEST_F(ProductRepositoryTest, UpdateNonexistentFails) {
    EXPECT_FALSE(repo->update("999", "Ghost", 0.0f, 0.0f));
}

TEST_F(ProductRepositoryTest, RemoveProductWorks) {
    EXPECT_TRUE(repo->remove(2));
    auto products = repo->list();
    EXPECT_EQ(products.size(), 1);
    EXPECT_NE(products[0]->get_id(), "2");
}

TEST_F(ProductRepositoryTest, RemoveNonexistentFails) {
    EXPECT_FALSE(repo->remove(12345));
}

TEST_F(ProductRepositoryTest, ValidateIdWorks) {
    EXPECT_TRUE(repo->validate_id(1));
    EXPECT_FALSE(repo->validate_id(999));
}

TEST_F(ProductRepositoryTest, ValidateStockChecksCorrectly) {
    EXPECT_TRUE(repo->validate_stock(1, 5));
    EXPECT_FALSE(repo->validate_stock(1, 50));  // prea mult
    EXPECT_FALSE(repo->validate_stock(1, -3));  // invalid
    EXPECT_FALSE(repo->validate_stock(999, 1)); // ID inexistent
}

