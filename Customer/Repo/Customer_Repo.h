//
// Created by ionut on 5/8/2025.
//

#ifndef CUSTOMER_REPO_H
#define CUSTOMER_REPO_H
#pragma once
#include "../Domain/Customer.h"
#include <vector>
#include <memory>

using namespace std;
using namespace Customer_Domain;

namespace Customer_Repo {

    class Customer_Repo {
    private:
        vector<shared_ptr<Customer>> customers;
        int nextId = 1; // id overlaps between customers and employees

    public:
        shared_ptr<Customer> create(const string& name, const string& forename,
                                    const string& email, const string& password,
                                    const string& address);

        bool update(int id, const string& address);

        bool remove(int id);

        Customer find_client_by_email(const string &email);
    };
}


#endif //CUSTOMER_REPO_H
