//
// Created by Simon Raul on 5/26/2025.
//

#include <gtest/gtest.h>
#include "../Data/Domain//User.h"

using namespace userdomain;

TEST(UserTest, ConstructorAndGetters) {
    User user("Popescu", "Ion", "ion.popescu@gmail.com", "parola123");

    EXPECT_EQ(user.get_name(), "Popescu");
    EXPECT_EQ(user.get_forename(), "Ion");
    EXPECT_EQ(user.get_email(), "ion.popescu@gmail.com");
    EXPECT_EQ(user.get_password(), "parola123");
}

TEST(UserTest, SetName) {
    User user("Initial", "Ion", "ion@example.com", "pass");
    user.set_name("NumeNou");

    EXPECT_EQ(user.get_name(), "NumeNou");
}

TEST(UserTest, SetForename) {
    User user("Nume", "Initial", "ion@example.com", "pass");
    user.set_forename("PrenumeNou");

    EXPECT_EQ(user.get_forename(), "PrenumeNou");
}

TEST(UserTest, SetEmail) {
    User user("Nume", "Prenume", "initial@example.com", "pass");
    user.set_email("nou@example.com");

    EXPECT_EQ(user.get_email(), "nou@example.com");
}

TEST(UserTest, SetPassword) {
    User user("Nume", "Prenume", "email@example.com", "initial");
    user.set_password("noua_parola");

    EXPECT_EQ(user.get_password(), "noua_parola");
}
