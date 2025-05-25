//
// Created by irisz on 5/2/2025.
//

#include "EmployeeRepo.h"
#include <iostream>
#include <fstream>

namespace employeerepo {

	std::vector<std::vector<std::string>> readFileSplitByColon(const std::string& filename) {
		std::vector<std::vector<std::string>> result;
		std::ifstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Error: Could not open file " << filename << std::endl;
			return result;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::vector<std::string> tokens;
			std::stringstream ss(line);
			std::string token;

			while (std::getline(ss, token, ':')) {
				tokens.push_back(token);
			}

			result.push_back(tokens);
		}

		file.close();
		return result;
	}

	shared_ptr<Employee> EmployeeRepository::create_with_id(const int &id, const string &name, const string &forename, const string &email, const string &password, const string &position, year_month_day birthday, float salary) {
		shared_ptr<Employee> new_employee = make_shared<Employee>(name, forename, email, password, position, birthday, salary);
		new_employee->set_id(id);
		employees.push_back(new_employee);
		return new_employee;
	}

	EmployeeRepository::EmployeeRepository(const string &filename) {
		int max= 1;
		std::vector<std::vector<std::string>> employees_vector = readFileSplitByColon(filename);
		for (int i = 0; i < employees_vector.size(); i++) {
			if (stoi(employees_vector[i][0]) > max) {
				max = stoi(employees_vector[i][0]);
			}
			create_with_id(stoi(employees_vector[i][0]),employees_vector[i][2],employees_vector[i][1],employees_vector[i][3],employees_vector[i][4],employees_vector[i][5], parse_date(employees_vector[i][6]), stof(employees_vector[i][7]));
		}
		nextId = max;
	}


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

	Employee EmployeeRepository::find_by_email(const string &email) {
		for (int i = 0; i < employees.size(); i++) {
			if (employees[i]->get_email() == email) {
				return *employees[i];
			}
		}
		throw runtime_error("Customer not found");
	}


}
