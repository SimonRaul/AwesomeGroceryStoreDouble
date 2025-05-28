//
// Created by anama on 5/22/2025.
//

#ifndef CLIENTMANAGEMENTCONTROLLER_H
#define CLIENTMANAGEMENTCONTROLLER_H

#include <string>
#include <fstream>
#include <memory>

#include "../../Data/Repo/Customer_Repo.h"
#include "OrderController.h"
#include "../../Data/Domain/Product.h"

using namespace std;
using namespace productdomain;
using namespace repository;

namespace controller {

class ClientManagementController {
private:
    Customer_Repo::Customer_Repo cus_repo;
    OrderController order_contr;

public:
    ClientManagementController(const string& filename, const OrderController &order_contr);
    void gdprAnonymize(const string &email);
    bool createCustomer(const string &name, const string &forename,
        const string &email, const string &password, const string &address);
    bool updateCustomer(int id, const string& address);
    bool removeCustomer(int id);
    vector<shared_ptr<Customer>> listByName();
    vector<shared_ptr<Customer>> listByEmail(const string &email);
    vector<shared_ptr<Customer>> listByProduct(const Product& product);
};

}

#endif //CLIENTMANAGEMENTCONTROLLER_H
