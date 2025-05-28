//
// Created by Simon Raul on 5/28/2025.
//

#include <gtest/gtest.h>
#include "../Data/Repo//EmployeeRepo.h"
#include "../Data/Domain/Employee.h"
#include <chrono>

using namespace employeerepo;
using namespace employeedomain;
using namespace std;
using namespace chrono;

class EmployeeRepoTest : public ::testing::Test {
protected:
    void SetUp() override {
        repo = std::make_unique<EmployeeRepository>("employees_test.txt");
    }

    std::unique_ptr<EmployeeRepository> repo;
};

TEST_F(EmployeeRepoTest, LoadInitialEmployeesFromFile) {
    auto employees = repo->list();
    ASSERT_EQ(employees.size(), 2);

    EXPECT_EQ(employees[0]->get_name(), "Ana");
    EXPECT_EQ(employees[1]->get_email(), "matei.ionescu@groceryco.com");
}

TEST_F(EmployeeRepoTest, CreateEmployeeIncrementsId) {
    year_month_day birth{year{1995}, month{4}, day{20}};
    auto new_emp = repo->create("Popescu", "Ion", "ion.popescu@example.com", "pw123", "Manager", birth, 4500.0f);

    ASSERT_NE(new_emp, nullptr);
    EXPECT_EQ(new_emp->get_name(), "Popescu");
    EXPECT_EQ(new_emp->get_position(), "Manager");

    auto employees = repo->list();
    EXPECT_EQ(employees.size(), 3);
}

TEST_F(EmployeeRepoTest, CreateWithIdWorksCorrectly) {
    year_month_day birth{year{1980}, month{3}, day{10}};
    auto emp = repo->create_with_id(10, "Test", "User", "test@example.com", "pw", "Tester", birth, 3900.0f);

    ASSERT_NE(emp, nullptr);
    EXPECT_EQ(emp->get_id(), 10);
    EXPECT_EQ(emp->get_email(), "test@example.com");
}

TEST_F(EmployeeRepoTest, UpdateEmployeeWorks) {
    year_month_day new_birth{year{1990}, month{12}, day{1}};
    bool updated = repo->update(1, "Supervisor", new_birth, 3600.5f);

    EXPECT_TRUE(updated);
    auto list = repo->list();
    EXPECT_EQ(list[0]->get_position(), "Supervisor");
    EXPECT_EQ(list[0]->get_salary(), 3600.5f);
    EXPECT_EQ(list[0]->get_birthday(), new_birth);
}

TEST_F(EmployeeRepoTest, UpdateNonexistentEmployeeFails) {
    year_month_day dummy{year{2000}, month{1}, day{1}};
    EXPECT_FALSE(repo->update(999, "Ghost", dummy, 0.0f));
}

TEST_F(EmployeeRepoTest, RemoveEmployeeById) {
    bool removed = repo->remove(2);
    EXPECT_TRUE(removed);

    auto remaining = repo->list();
    EXPECT_EQ(remaining.size(), 1);
    EXPECT_NE(remaining[0]->get_id(), 2);
}

TEST_F(EmployeeRepoTest, RemoveNonexistentEmployeeFails) {
    EXPECT_FALSE(repo->remove(999));
}

TEST_F(EmployeeRepoTest, FindByEmailSuccess) {
    Employee emp = repo->find_by_email("ana.petrescu@groceryco.com");
    EXPECT_EQ(emp.get_forename(), "Petrescu");
}

TEST_F(EmployeeRepoTest, FindByEmailThrowsIfNotFound) {
    EXPECT_THROW(repo->find_by_email("ghost@domain.com"), std::runtime_error);
}
