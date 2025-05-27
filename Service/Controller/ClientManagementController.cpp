#include "ClientManagementController.h"
#include "../../Data/Repo/Customer_Repo.h"
#include <set>
#include "../../Data/Domain/OrderDomain.h"

using namespace std;
using namespace Customer_Repo;
using namespace Customer_Domain;
using namespace repository;
using namespace domain;

namespace controller {

ClientManagementController::ClientManagementController(::Customer_Repo::Customer_Repo &cus_repo, OrderRepo &order_repo)
    : cus_repo(cus_repo), order_repo(order_repo) {}



void ClientManagementController::gdprAnonymize(const string &email) {
    Customer_Domain::Customer customer = cus_repo.find_by_email(email);
    ofstream file;
    file.open("gdprdata.txt");
    file << "Kunde-" << customer.get_id() <<" Unbekannt" << ":" << "null" << ":" << "null" << ":" << "gdprDeleted=true" << ":" << "null" << '\n';
    file.close();
}

bool ClientManagementController::createCustomer(const string &name, const string &forename,
    const string &email, const string &password, const string &address) {
    try {
        cus_repo.create(name, forename, email, password, address);
        return true;
    } catch (const exception& e) {
        return false;
    }
}

bool ClientManagementController::updateCustomer(int id, const string& address) {
    return cus_repo.update(id, address);
}

bool ClientManagementController::removeCustomer(int id) {
    return cus_repo.remove(id);
}

vector<shared_ptr<Customer>> ClientManagementController::listByName() {
    vector<shared_ptr<Customer>> customers = cus_repo.list();
    sort(customers.begin(), customers.end(), 
        [](const shared_ptr<Customer>& a, const shared_ptr<Customer>& b) {
            return a->get_name() < b->get_name();
        });
    sort(customers.begin(), customers.end(),
        [](const shared_ptr<Customer>& a, const shared_ptr<Customer>& b) {
            return a->get_forename() < b->get_forename();
        });
    return customers;
}

vector<shared_ptr<Customer>> ClientManagementController::listByEmail(const string &email) {
    vector<shared_ptr<Customer>> customers = cus_repo.list();
    vector<shared_ptr<Customer>> filtered;
    copy_if(customers.begin(), customers.end(), back_inserter(filtered),
        [&email](const shared_ptr<Customer>& c) {
            return c->get_email() == email;
        });
    return filtered;
}

vector<shared_ptr<Customer>> ClientManagementController::listByProduct(const Product& product) {
    vector<shared_ptr<Customer>> customers;
    set<int> customerIds;

    const vector<OrderDomain>& orders = order_repo.getOrders();

    for (const auto& order : orders) {
        const vector<pair<Product, int>>& orderProducts = order.getProducts();
        
        for (const auto& orderProduct : orderProducts) {
            if (orderProduct.first.get_id() == product.get_id()) {
                Customer customer = order.getCustomer();
                
                if (!customerIds.contains(customer.get_id())) {
                    customerIds.insert(customer.get_id());
                    auto customerPtr = make_shared<Customer>(customer);
                    customers.push_back(customerPtr);
                }
                break;
            }
        }
    }

    return customers;
}

}