//
// Created by irisz on 5/2/2025.
//
#include "Employee.h"
#include <string>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;
using namespace userdomain;

namespace employeedomain {

	// Constructor definition
	Employee::Employee(string name, string forename, string email, string password,
					   string position, year_month_day birthday, float salary)
		: User(name, forename, email, password), // Call to base class constructor
		  position(position), birthday(birthday), salary(salary) {}

	// Getter for position
	string Employee::get_position() {
		return position;
	}

	// Getter for birthday
	year_month_day Employee::get_birthday() {
		return birthday;
	}

	// Getter for salary
	float Employee::get_salary() {
		return salary;
	}
    // Getter for id
	int Employee::get_id() const {
		return id;
	}

	// Setter for position
	void Employee::set_position(string new_position) {
		position = new_position;
	}

	// Setter for birthday
	void Employee::set_birthday(year_month_day new_birthday) {
		birthday = new_birthday;
	}

	// Setter for salary
	void Employee::set_salary(float new_salary) {
		salary = new_salary;
	}

	// Setter for id
	void Employee::set_id(int new_id) {
		id = new_id;
	}


} // namespace employeedomain
