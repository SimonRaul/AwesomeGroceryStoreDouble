//
// Created by ionut on 5/8/2025.
//

#ifndef CUSTOMER_REPO_H
#define CUSTOMER_REPO_H
#pragma once
#include "../Domain/Customer.h"
#include <vector>
#include <memory>
#include <algorithm>

#include "IRepo.h"

using namespace std;
using namespace Customer_Domain;

namespace Customer_Repo {

    class Customer_Repo: public IRepo<Customer_Repo, Customer> {
    private:
        vector<shared_ptr<Customer>> customers;
        int nextId = 1; // id overlaps between customers and employees

    public:

        explicit Customer_Repo(const string& filename);

        shared_ptr<Customer> create(const string& name, const string& forename,
                                    const string& email, const string& password,
                                    const string& address);

        shared_ptr<Customer> create_with_id(const int& id, const string& name, const string& forename,
                                    const string& email, const string& password,
                                    const string& address);
        bool update(int id, const string& address);

        bool remove(int id) override;

        Customer find_by_email(const string &email) override;
        vector<shared_ptr<Customer>> list() override;
    };
}


#endif //CUSTOMER_REPO_H
