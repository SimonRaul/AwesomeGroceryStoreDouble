//
// Created by Simon Raul on 5/26/2025.
//

#include <gtest/gtest.h>
#include "../Data/Domain/Product.h"

using namespace productdomain;

TEST(ProductTest, ConstructorWithAllFields) {
    Product p("001", "Milk", 4.99f, 2.5f);

    EXPECT_EQ(p.get_id(), "001");
    EXPECT_EQ(p.get_name(), "Milk");
    EXPECT_FLOAT_EQ(p.get_price(), 4.99f);
    EXPECT_FLOAT_EQ(p.get_quantity(), 2.5f);
}

TEST(ProductTest, ConstructorWithAutoId) {
    Product p("Bread", 3.50f, 1.0f);

    EXPECT_FALSE(p.get_id().empty());  // ID-ul trebuie să fie generat
    EXPECT_EQ(p.get_name(), "Bread");
    EXPECT_FLOAT_EQ(p.get_price(), 3.50f);
    EXPECT_FLOAT_EQ(p.get_quantity(), 1.0f);
}

TEST(ProductTest, SettersUpdateFieldsCorrectly) {
    Product p("001", "Milk", 4.99f, 2.5f);

    p.set_id("002");
    p.set_name("Cheese");
    p.set_price(9.99f);
    p.set_quantity(5.0f);

    EXPECT_EQ(p.get_id(), "002");
    EXPECT_EQ(p.get_name(), "Cheese");
    EXPECT_FLOAT_EQ(p.get_price(), 9.99f);
    EXPECT_FLOAT_EQ(p.get_quantity(), 5.0f);
}
