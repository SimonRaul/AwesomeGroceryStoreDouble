//
// Created by irisz on 5/2/2025.
//

#ifndef EMPLOYEEREPO_H
#define EMPLOYEEREPO_H

#pragma once
#include "../Domain/Employee.h"
#include <vector>
#include <memory>
#include <optional>

using namespace std;
using namespace employeedomain;

namespace employeerepo {

	class EmployeeRepository {
	private:
		vector<shared_ptr<Employee>> employees;
		int nextId = 1;

	public:
		shared_ptr<Employee> create(const string& name, const string& forename,
									const string& email, const string& password,
									const string& position, year_month_day birthday,
									float salary);

		bool update(int id, const string& position, year_month_day birthday, float salary);

		bool remove(int id);
	};

}
#endif //EMPLOYEEREPO_H
