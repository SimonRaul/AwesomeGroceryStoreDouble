//
// Created by ionut on 5/15/2025.
//

#include "Customer_UI.h"
#include <iostream>
// #include <typeinfo>

#include "../../Service/Controller/ProductController.h"
Customer_UI::Customer_UI(const std::string& cus_file, const std::string& prod_file, const std::string& order_file) :cus_repo(cus_file), product_cont(prod_file), order_cont(controller::OrderController(order_file, product_cont)){}

std::string Customer_UI::main_menu() {
    return "Choose an option:\n1 - See Products\n2 - Reserve Product\n3 - See orders\n4 - See order status (by order ID)\n5 - Exit\n------------------- * * * -------------------\n";

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
        // std::cout<<"Option: ";
        option = input_integer();
        std::cout<<std::endl;
        if (option == 1) {
            // std::cout<<"suntem cooked!\n";
            std::vector<std::shared_ptr<Product>> products;
            products = product_cont.listProducts();
            std::cout<<"Product list:\n";
            for (auto& product : products) {
                cout<<"ID: "<<product->get_id()<<" Name: "<<product->get_name()<<" Price: "<<product->get_price()<<" Quantity: "<<product->get_quantity()<<"\n";
            }
            cout<<"\n------------------- * * * -------------------\n";
        }
        else if (option == 2) {
            std::vector<std::shared_ptr<Product>> products;
            products = product_cont.listProducts();
            std::vector<pair<std::shared_ptr<Product>,int>> ordered_products;
            std::vector<pair<int,int>> ordered_products_id;
            int product_id = -1;
            int quantity = -1;
            while (product_id != 0) {
                cout<<"Please enter the id of the products you want to reserve or number 0 to stop:\n";
                product_id = input_integer();
                // validare ID
                if (quantity && product_id != 0){
                    cout<<"Please enter the quantity:\n";
                quantity = input_integer();
            ordered_products_id.push_back({product_id,quantity});
                }
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
            vector<pair<Product,float>> product_vec;             // vectorul dorit

            for (const auto& ptr : ordered_products) {
                if (ptr.first) {
                    product_vec.push_back({*ptr.first,float(ptr.second)});  // se copiază obiectul din shared_ptr
                }
            }
            order_cont.createReservation(*customer,product_vec);
        }
        else if (option == 3) {
            cout<<"Your orders are:\n";
            for (auto& order: order_cont.getOrdersByCustomer(customer)) {
                cout<<order;
            }
        }
        else if (option == 4) {
            cout<<"Please give order ID:\n";
            int id = input_integer();
            if (order_cont.validateID(id)) {
                domain::OrderDomain order = order_cont.getOrderByID(id);
                cout<<order.status_to_string(order.getStatus());
            }
            else {
                cout<<"ID was not found!\n";
            }
        }
        else if (option == 5) {
            break;
        }
        else {
            cout<<"Please give valid input!!!\n";
        }
    }
}


