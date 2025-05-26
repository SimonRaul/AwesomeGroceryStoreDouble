//
// Created by Simon Raul on 5/26/2025.
//

#include <gtest/gtest.h>
#include "../Data/Domain/Employee.h"
#include <chrono>

using namespace employeedomain;
using namespace std;
using namespace chrono;

TEST(EmployeeTest, ConstructorAndGetters) {
    year_month_day birth_date{year{1990}, month{5}, day{15}};
    Employee emp("Ionescu", "Maria", "maria.ionescu@example.com", "parola123",
                 "Manager", birth_date, 4500.0f);

    EXPECT_EQ(emp.get_name(), "Ionescu");
    EXPECT_EQ(emp.get_forename(), "Maria");
    EXPECT_EQ(emp.get_email(), "maria.ionescu@example.com");
    EXPECT_EQ(emp.get_password(), "parola123");
    EXPECT_EQ(emp.get_position(), "Manager");
    EXPECT_EQ(emp.get_birthday(), birth_date);
    EXPECT_FLOAT_EQ(emp.get_salary(), 4500.0f);
}

TEST(EmployeeTest, Setters) {
    year_month_day birth_date{year{1990}, month{5}, day{15}};
    Employee emp("Ionescu", "Maria", "maria.ionescu@example.com", "parola123",
                 "Manager", birth_date, 4500.0f);

    emp.set_position("Director");
    emp.set_salary(5200.5f);
    year_month_day new_birthday{year{1991}, month{6}, day{20}};
    emp.set_birthday(new_birthday);
    emp.set_id(17);

    EXPECT_EQ(emp.get_position(), "Director");
    EXPECT_FLOAT_EQ(emp.get_salary(), 5200.5f);
    EXPECT_EQ(emp.get_birthday(), new_birthday);
    EXPECT_EQ(emp.get_id(), 17);
}
