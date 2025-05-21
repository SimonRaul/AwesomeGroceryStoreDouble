//
// Created by ionut on 5/8/2025.
//

#include "Customer.h"
#include <string>
#include <chrono>

#include "../../Data/Domain/User.h"

using namespace std;
using namespace chrono;
using namespace userdomain;

namespace Customer_Domain {
    // Constructor for customer
    Customer::Customer(const string &name, const string &forename, const string &email, const string &password, const string &address)
        // Call for the parent constructor
        : User(name, forename, email, password)
    {
        this->address = address;
    }

    // Getter for address
    string Customer::get_address() {
        return address;
    }

    int Customer::get_id() const {
        return id;
    }

    void Customer::set_address(string new_address) {
        this->address = new_address;
    }

    void Customer::set_id(int new_id) {
        this->id = new_id;
    }

}