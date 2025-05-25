//
// Created by irisz on 5/2/2025.
//

#ifndef EMPLOYEEREPO_H
#define EMPLOYEEREPO_H

#pragma once
#include "../Domain/Employee.h"
#include "IRepo.h"
#include <vector>
#include <memory>
#include <chrono>
#include <iostream>
#include <sstream>

using namespace std;
using namespace employeedomain;

namespace employeerepo {

	class EmployeeRepository: public IRepo<EmployeeRepository, Employee> {
	private:
		vector<shared_ptr<Employee>> employees;
		int nextId = 1;

	public:

		explicit EmployeeRepository(const string& filename);

		year_month_day parse_date(const std::string& str) {
			int y, m, d;
			char dash1, dash2;
			std::istringstream ss(str);
			ss >> y >> dash1 >> m >> dash2 >> d;

			if (!ss || dash1 != '-' || dash2 != '-') {
				throw std::runtime_error("Invalid date format");
			}

			return std::chrono::year{y}
			/ std::chrono::month{static_cast<unsigned>(m)}
			/ std::chrono::day{static_cast<unsigned>(d)};
		}

		shared_ptr<Employee> create_with_id(const int& id, const string& name, const string& forename,
									const string& email, const string& password,
									const string& position, year_month_day birthday,
									float salary);

		shared_ptr<Employee> create(const string& name, const string& forename,
									const string& email, const string& password,
									const string& position, year_month_day birthday,
									float salary);

		bool update(int id, const string& position, year_month_day birthday, float salary);

		bool remove(int id) override;

		Employee find_by_email(const string& email) override;
	};

}
#endif //EMPLOYEEREPO_H
