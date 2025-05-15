//
// Created by irisz on 5/2/2025.
//
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "../../User/Domain/User.h"
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
};

}


#endif //EMPLOYEE_H
