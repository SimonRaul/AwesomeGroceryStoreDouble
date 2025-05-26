//
// Created by ionut on 5/8/2025.
//

#include "Customer_Repo.h"
#include <fstream>
#include <iostream>

namespace Customer_Repo {
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

    shared_ptr<Customer> Customer_Repo::create_with_id(const int &id, const string &name, const string &forename, const string &email, const string &password, const string &address) {
        shared_ptr<Customer> new_customer = make_shared<Customer>(name,forename,email,password,address);
        new_customer->set_id(id);
        customers.push_back(new_customer);
        return new_customer;
    }

    Customer_Repo::Customer_Repo(const string &filename) {
        int max= 1;
        std::vector<std::vector<std::string>> customers_vector = readFileSplitByColon(filename);
        for (int i = 0; i < customers_vector.size(); i++) {
            if (stoi(customers_vector[i][0]) > max) {
                max = stoi(customers_vector[i][0]);
            }
            create_with_id(stoi(customers_vector[i][0]),customers_vector[i][1],customers_vector[i][2],customers_vector[i][3],customers_vector[i][4],customers_vector[i][5]);
        }
        nextId = max;
    }

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

    vector<shared_ptr<Customer>> Customer_Repo::list()
    {
        return customers;
    }

}
