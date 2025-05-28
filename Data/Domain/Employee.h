//
// Created by irisz on 5/2/2025.
//
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"
#include <string>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;
using namespace userdomain;

namespace employeedomain{

class Employee: public User {
	private:
    string position;
	year_month_day birthday;
	float salary;
    int id;

	public:
	// C-Tor
	Employee(string name = "", string forename = "", string email = "", string password = "", string position = "", year_month_day birthday = year_month_day(), float salary = 0.0);

	// Getters
	string get_position();
	year_month_day get_birthday();
	float get_salary();
    int get_id() const;

	// Setters
	void set_position(string new_position);
	void set_birthday(year_month_day new_birthday);
	void set_salary(float new_salary);
	void set_id(int new_id);

	friend std::ostream& operator<<(std::ostream& os, Employee& employee) {
		os << "ID: " << employee.get_id() << ", "
		   << "Name: " << employee.get_name() << ", "
		   << "Forename: " << employee.get_forename() << ", "
		   << "Email: " << employee.get_email() << ", "
		   << "Password: " << employee.get_password() << ", "
		   << "Position: " << employee.get_position() << ", "
		   << "Birthday: " << employee.get_birthday() << ", "
		   << "Salary: " << employee.get_salary() << "\n";
		return os;
	}

};

}


#endif //EMPLOYEE_H
