//
// Created by ionut on 5/8/2025.
//

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "User.h"
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace userdomain;

namespace Customer_Domain{
    class Customer: public User {
    private:
        int id;
        string address;
        bool GdprDeleted = true;// functionality is work in progress <3

    public:
        // Constructor
        Customer(const string &name = "", const string &forename = "", const string &email = "", const string &password = "", const string &address = "");

        // getters
        int get_id() const;
        string get_address();

        // setters
        void set_id(int new_id);
        void set_address(string new_address);
    };
}


#endif //CUSTOMER_H