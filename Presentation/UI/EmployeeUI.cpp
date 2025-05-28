//
// Created by ionut on 5/15/2025.
//

#include "./EmployeeUI.h"
#include "../../Data/Domain/OrderDomain.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <ctime>
#include <iomanip>


EmployeeUI::EmployeeUI(const std::string &prod_file, const std::string &order_file, const std::string &cus_file)
    : prod_contr(prod_file), order_contr(order_file, prod_contr), client_mgn(cus_file, order_contr) {}

std::string EmployeeUI::main_menu() {
    return "Choose an option:\n"
           "1 - Client management\n"
           "2 - Order management\n"
           "3 - Product management\n"
           "0 - Exit\n------------------- * * * -------------------\n";
}

std::string EmployeeUI::client_menu() {
    return "Choose an option:\n"
           "1 - List clients\n"
           "2 - Search client by email\n"
           "3 - Search clients by bought products\n"
           "4 - Add client\n"
           "5 - Update client by ID\n"
           "6 - Remove client\n"
           "7 - GDPR anonymise\n"
           "0 - Back to main men\n------------------- * * * -------------------\n";
}

std::string EmployeeUI::order_menu() {
    return "Choose an option:\n"
           "1 - List all reservations\n"
           "2 - List reservation by status\n"
           "3 - Show total income in a year\n"
           "4 - Show total income in a month\n"
           "5 - Update order by ID\n"
           "6 - Mark order as completed\n"
           "7 - Mark order as confirmed\n"
           "8 - Take order\n"
           "0 - Back to main menu\n------------------- * * * -------------------\n";
}

std::string EmployeeUI::product_menu() {
    return "Choose an option:\n"
           "1 - Create a product\n"
           "2 - List all products\n"
           "0 - Back to main menu\n------------------- * * * -------------------\n";
}


void EmployeeUI::run_main_menu(Employee* employee) {
    bool exit = false;
    while (!exit) {
        std::cout << main_menu();
        int option;
        option = input_integer();
        std::cout<<'\n';
        if (option == 1) {
            std::cout<<"Client management\n";
            run_client_menu(employee);
        }
        else if (option == 2) {
            std::cout<<"Order management\n";
            run_order_menu(employee);
        }
        else if (option == 3) {
            std::cout<<"Product management\n";
            run_product_menu(employee);
        }
        else if (option == 0) {
            exit = true;
        }
        else {
            std::cout<<"Please give valid input!!!\n";
        }
    }
}

void EmployeeUI::run_client_menu(Employee* employee) {
    bool exit = false;

    while (!exit) {
        std::cout << client_menu();
        int option;
        option = input_integer();
        std::cout<<'\n';

        if (option == 1) {
            std::vector<std::shared_ptr<Customer>> clients;
            clients = client_mgn.listByName();
            std::cout<<"Customers list:\n";
            for (auto& client : clients) {
                cout << *client << "\n";
            }
            cout<<"\n------------------- * * * -------------------\n";
        }
        else if (option == 2) {
            std::cout<<"Please enter the email of the client you want to search:\n";
            std::string email = input_string();
            std::vector<std::shared_ptr<Customer>> clients;
            clients = client_mgn.listByEmail(email);
            std::cout<<"Customers list:\n";
            for (auto& client : clients) {
                cout << *client << "\n";
            }
            cout<<"\n------------------- * * * -------------------\n";
        }
        else if (option == 3) {
            std::cout<<"Please enter the id of the product you want to search:\n";
            int id = input_integer();
            std::shared_ptr<Product> product;
            product = prod_contr.getProductById(id);
            std::vector<std::shared_ptr<Customer>> clients;
            clients = client_mgn.listByProduct(*product);
            std::cout<<"Customers list:\n";
            for (auto& client : clients) {
                cout << *client << "\n";
            }
            cout<<"\n------------------- * * * -------------------\n";
        }
        else if (option == 4) {
            std::cout<<"Please enter the name of the client:\n";
            string name = input_string();
            std::cin>>name;
            std::cout<<"Please enter the forename of the client:\n";
            string forename = input_string();
            std::cin>>forename;
            std::cout<<"Please enter the email of the client:\n";
            string email = input_string();
            std::cin>>email;
            std::cout<<"Please enter the password of the client:\n";
            string password = input_string();
            std::cin>>password;
            std::cout<<"Please enter the address of the client:\n";
            string address = input_string();
            std::cin>>address;
            client_mgn.createCustomer(name, forename, email, password, address);
        }
        else if (option == 5) {
            std::cout<<"Please enter the id of the client:\n";
            int id = input_integer();
            // needs validation
            std::cout<<"Please enter the updated adress of the client:\n";
            string address = input_string();
            client_mgn.updateCustomer(id, address);
        }
        else if (option == 6) {
            std::cout<<"Please enter the id of the client:\n";
            int id = input_integer();
            client_mgn.removeCustomer(id);
        }
        else if (option == 7) {
            std::cout<<"Please enter the email of the client:\n";
            string email = input_string();
            client_mgn.gdprAnonymize(email);
        }
        else if (option == 0) {
            exit = true;
        }
        else {
            std::cout<<"Please give valid input!!!\n";
        }
    }
}

static domain::OrderStatus string_to_status(const std::string& status) {
    static const std::unordered_map<std::string, domain::OrderStatus> status_map = {
        {"Reservation", domain::OrderStatus::Reservation},
        {"Confirmed", domain::OrderStatus::Confirmed},
        {"Completed", domain::OrderStatus::Completed}
    };

    auto it = status_map.find(status);
    if (it != status_map.end()) {
        return it->second;
    }

    // Default to Reservation if invalid
    return domain::OrderStatus::Reservation;
}


void EmployeeUI::run_order_menu(Employee* employee) {
    bool exit = false;
    while (!exit) {
        cout << order_menu();
        int option;
        option = input_integer();
        std::cout<<'\n';
        if (option == 1) {
            std::cout<<"List all reservations\n";
            std::vector<domain::OrderDomain> orders = order_contr.getOrders();
            for (const auto& order : orders) {
                cout << order << "\n";
            }
        }
        else if (option == 2) {
            std::cout<<"Please enter the status of the orders you want to search:\n";
            std::string status = input_string();
            domain::OrderStatus order_status = string_to_status(status);
            std::vector<domain::OrderDomain> orders = order_contr.getOrdersByStatus(order_status);
            for (const auto& order : orders) {
                cout << order << "\n";
            }
        }
        else if (option == 3) {
            std::cout<<"Please enter the year you want to search:\n";
            int year = input_integer();
            std::cout<<order_contr.getTotalOrdersInYear(year) << "\n";
        }
        else if (option == 4) {
            std::cout<<"Please enter the month you want to search:\n";
            int month = input_integer();
            std::cout<<order_contr.getTotalOrdersInMonth(month) << "\n";
        }
        else if (option == 5) {
            std::cout<<"Please enter the order ID you want to update:\n";
            int id = input_integer();
            // validate if employee has order or no
            std::vector<pair<Product,float>> ordered_products;
            ordered_products = order_contr.get_products_from_id(id);
            if (!ordered_products.empty()) {
                cout<<"Current products in order are: \n";
                for (auto& product : ordered_products) {
                    cout<<product.first<<"\nQuantity ordered: "<<product.second<<endl;
                }

            std::vector<pair<Product,float>> new_products;
            std::vector<pair<int,float>> new_products_id;
            int product_id = -1;
            float quantity;
            while (product_id != 0) {
                cout<<"Please enter the id of the products you want to put in the order or number 0 to stop:\n";
                product_id = input_integer();
                // validare ID
                if (product_id != 0){
                    cout<<"Please enter the quantity:\n";
                    quantity = input_float();
                    new_products_id.push_back({product_id,quantity});
                }
                // validare stoc
            }
            std::vector<std::shared_ptr<Product>> products;
            products = prod_contr.listProducts();
            while (!new_products_id.empty()) {
                pair<int,float> current_product = new_products_id.back();
                new_products_id.pop_back();
                for (int i = 0; i < products.size(); i++) {
                    if (stoi(products[i]->get_id()) == current_product.first) {
                        new_products.push_back({*products[i], current_product.second});
                    }
                }
            }

            order_contr.updateOrder(id,new_products);
        }
            else {
                cout<<"No order found\n";
            }
        }
        else if (option == 6) {
            std::cout<<"Please enter the order ID you want to mark as completed:\n";
            int id = input_integer();
            order_contr.setOrderStatus(id, domain::OrderStatus::Completed);
        }
        else if (option == 7) {
            std::cout<<"Please enter the order ID you want to mark as confirmed:\n";
            int id = input_integer();
            order_contr.setOrderStatus(id, domain::OrderStatus::Confirmed);
        }
        else if (option == 8) {
            std::cout<<"Please enter the order ID you want to take:\n";
            int id = input_integer();
            order_contr.assignEmployeeIfUnassigned(id, *employee);
        }
        else if (option == 0) {
            exit = true;
        }
        else {
            std::cout<<"Please give valid input!!!\n";
        }
    }
}

void EmployeeUI::run_product_menu(Employee* employee) {
    bool exit = false;
    while (!exit) {
        cout << product_menu();
        int option;
        option = input_integer();
        std::cout<<'\n';
        if (option == 1) {
            std::cout<<"Create a product\n";
            std::cout<<"Please enter the name of the product:\n";
            string name = input_string();
            std::cin>>name;
            std::cout<<"Please enter the price of the product:\n";
            float price = input_float();
            std::cin>>price;
            std::cout<<"Please enter the quantity of the product:\n";
            int quantity = input_integer();
            std::cin>>quantity;
            prod_contr.addProduct(name, price, quantity);
        }
        else if (option == 2) {
            std::cout<<"List all products\n";
            std::vector<std::shared_ptr<Product>> products = prod_contr.listProducts();
            for (const auto& product : products) {
                std::cout << *product << "\n";
            }
        }
        else if (option == 0) {
            exit = true;
        }
        else {
            std::cout<<"Please give valid input!!!\n";
        }
    }
}

int EmployeeUI::input_integer() {
            int input;
            bool valid = false;
            while (!valid) {
                std::cout << "Enter number: " ;
                std::cin >> input;
                if(std::cin.fail())
                {
                    std::cout<<"Please enter a number...\n";
                    valid = false;
                }
                else valid = true;
            }
            std::cout<<"\n";
            return input;
}

float EmployeeUI::input_float() {
    float input;
    bool valid = false;
    while (!valid) {
        std::cout << "Enter floating point number: " ;
        std::cin >> input;
        if(std::cin.fail())
        {
            std::cout<<"Please enter a number...\n";
            valid = false;
        }
        else valid = true;
    }
    std::cout<<"\n";
    return input;
}

std::string EmployeeUI::input_string() {
    std::string input;
    bool valid = false;
    while (!valid) {
        std::cout << "Enter a string of characters: " ;
        std::cin >> input;
        if(std::cin.fail())
        {
            std::cout<<"Please enter a string of characters...\n";
            valid = false;
        }
        else valid = true;
    }
    std::cout<<"\n";
    return input;
}

void EmployeeUI::create_instance() {
    return;
}

void EmployeeUI::remove_instance() {
    return;
}

void EmployeeUI::update_instance() {
    return;
}

