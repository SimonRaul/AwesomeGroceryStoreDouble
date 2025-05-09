//
// Created by irisz on 5/2/2025.
//

#include "EmployeeRepo.h"

namespace employeerepo {

	shared_ptr<Employee> EmployeeRepository::create(const string& name, const string& forename,
		const string& email, const string& password, const string& position,
		year_month_day birthday, float salary) {

		auto employee = make_shared<Employee>(name, forename, email, password, position, birthday, salary);
		employee->set_id(nextId++);
		employees.push_back(employee);
		return employee;
	}

	bool EmployeeRepository::update(int id, const string& position,
									year_month_day birthday, float salary) {
		for (auto& emp : employees) {
			if (emp->get_id() == id) {
				emp->set_position(position);
				emp->set_birthday(birthday);
				emp->set_salary(salary);
				return true;
			}
		}
		return false;
	}

	bool EmployeeRepository::remove(int id) {
		for (auto it = employees.begin(); it != employees.end(); ++it) {
			if ((*it)->get_id() == id) {
				employees.erase(it);
				return true;
			}
		}
		return false;
	}

}
