//
// Created by ionut on 5/15/2025.
//

#include "Customer_UI.h"
#include <iostream>
// #include <typeinfo>

#include "../../Service/Controller/ProductController.h"
Customer_UI::Customer_UI(const std::string& cus_file, const std::string& prod_file, const std::string& order_file) :cus_repo(cus_file), product_cont(prod_file), order_cont(controller::OrderController(order_file, product_cont)){}

std::string Customer_UI::main_menu() {
    return "Choose an option:\n1 - Change Password\n2 - Reserve Product\n3 - See Products\n4 - See orders\n5 - See order status (by order ID)\n6 - Exit\n━━━━━━━━━━ ✦ ✧ ✦ ━━━━━━━━━━\n";

}

int Customer_UI::input_integer() {
    int input;
    bool valid = false;
    while (!valid) {
        cout << "Enter number: " ;
        cin >> input;
        if(cin.fail())
            {
            cout<<"Please enter a number...\n";
            valid = false;
            }
        else valid = true;
    }
    cout<<"\n";
    return input;
}

std::string Customer_UI::input_string() {
    std::string input;
    bool valid = false;
    while (!valid) {
        cout << "Enter a string of characters: " ;
        cin >> input;
        if(cin.fail())
        {
            cout<<"Please enter a string of characters...\n";
            valid = false;
        }
        else valid = true;
    }
    cout<<"\n";
    return input;
}

void Customer_UI::create_instance() {
    return;
}

void Customer_UI::remove_instance() {
    return;
}

void Customer_UI::update_instance() {
    return;
}

void Customer_UI::run(Customer* customer) {
    while (true) {
        std::cout<<main_menu();
        int option;
        std::cout<<"Option: ";
        std::cin>>option;
        std::cout<<std::endl;
        if (option == 1) {
            std::cout<<"suntem cooked!";
            break;
        }
        else if (option == 2) {
            std::vector<std::shared_ptr<Product>> products;
            products = product_cont.listProducts();
            std::vector<pair<std::shared_ptr<Product>,int>> ordered_products;
            std::vector<pair<int,int>> ordered_products_id;
            cout<<"Please enter the id of the products you want to reserve or number 0 to stop:\n";
            int product_id = -1;
            int quantity = -1;
            while (product_id != 0) {
                product_id = input_integer();
                // validare ID
                cout<<"Please enter the quantity:\n";
                if (quantity)
                quantity = input_integer();
                ordered_products_id.push_back({product_id,quantity});
                // validare stoc
            }
            while (!ordered_products_id.empty()) {
                pair<int,int> current_product = ordered_products_id.back();
                ordered_products_id.pop_back();
                for (int i = 0; i < products.size(); i++) {
                    if (stoi(products[i]->get_id()) == current_product.first) {
                        ordered_products.push_back({products[i], current_product.first});
                    }
                }
            }
            order_cont.createReservation(customer,ordered_products);
        }
    }
}


