//
// Created by ionut on 5/8/2025.
//

#include "Customer_Repo.h"

namespace Customer_Repo {

    shared_ptr<Customer> Customer_Repo::create(const string &name, const string &forename,
        const string &email, const string &password, const string &address)
    {
        shared_ptr<Customer> new_customer = make_shared<Customer>(name,forename,email,password,address);
        new_customer->set_id(nextId);
        nextId++;
        customers.push_back(new_customer);
        return new_customer;
    }

    bool Customer_Repo::update(int id, const string &address) {
        for (auto& customer : customers) {
            if (customer->get_id() == id) {
                customer->set_address(address);
                return true;
            }
        }
        return false;
    }

    bool Customer_Repo::remove(int id) {
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if ((*it)->get_id() == id) {
                customers.erase(it);
                return true;
            }
        }
        return false;
    }

    Customer Customer_Repo::find_by_email(const string& email) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i]->get_email() == email) {
                return *customers[i];
            }
        }
        throw runtime_error("Customer not found");
    }

}