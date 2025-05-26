//
// Created by Simon Raul on 5/26/2025.
//

#include <gtest/gtest.h>
#include "../Service/Controller/UserController.h"
#include <fstream>

using namespace usercontroller;

class UserControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
        controller = new UserController("Test", "User",
                                        "AccountsTest",
                                        "clientsTest.txt",
                                        "employees_test.txt");
    }

    void TearDown() override {
        delete controller;
    }

    UserController* controller;
};

TEST_F(UserControllerTest, LoginClientSuccess) {
    controller->login("john.smith@example.com", "pass123");
    User* u = controller->get_current_user();
    ASSERT_NE(u, nullptr);
    EXPECT_EQ(u->get_email(), "john.smith@example.com");
}

TEST_F(UserControllerTest, LoginEmployeeSuccess) {
    controller->login("ana.petrescu@groceryco.com", "fructe123");
    User* u = controller->get_current_user();
    ASSERT_NE(u, nullptr);
    EXPECT_EQ(u->get_email(), "ana.petrescu@groceryco.com");
}

TEST_F(UserControllerTest, LoginFailWrongPassword) {
    controller->login("john.smith@example.com", "wrongpass");
    User* u = controller->get_current_user();
    EXPECT_EQ(u->get_email(), "");
}

TEST_F(UserControllerTest, IsLoggedInBeforeAndAfterLogin) {
    EXPECT_FALSE(controller->is_logged_in());
    controller->login("john.smith@example.com", "pass123");
    EXPECT_TRUE(controller->is_logged_in());
}

TEST_F(UserControllerTest, UpdatePasswordSuccess) {
    bool result = controller->update_password("john.smith@example.com", "pass123", "newpass789");
    EXPECT_TRUE(result);

    std::ifstream in("AccountsTest");
    std::string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.find("john.smith@example.com:newpass789:client") != std::string::npos) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
    controller->update_password("john.smith@example.com", "newpass789", "pass123");
}

TEST_F(UserControllerTest, CreateAccountAddsNewClient) {
    bool created = controller->create_account("Popescu", "Ion", "ion.popescu@example.com", "ionpass", "Str. Lalelelor 5");
    EXPECT_TRUE(created);

    std::ifstream in("AccountsTest");
    std::string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.find("ion.popescu@example.com:ionpass:client") != std::string::npos) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}
