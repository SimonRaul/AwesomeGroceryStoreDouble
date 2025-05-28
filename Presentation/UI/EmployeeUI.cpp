//
// Created by ionut on 5/15/2025.
//

#include "./EmployeeUI.h"
#include <iostream>

std::string EmployeeUI::main_menu() {
    return "Choose an option:\n1 - Order management\n2 - Client management\n3 - Edit personal details\n4 - Exit\n━━━━━━━━━━ ✦ ✧ ✦ ━━━━━━━━━━\n";
}

std::string EmployeeUI::order_menu() {
    return "Choose an option:\n1 - List reservations\n2 - Process order by ID\n3 - Mark order as completed\n4 - Delete orders\n5 - Back\n━━━━━━━━━━ ✦ ✧ ✦ ━━━━━━━━━━\n";
}

std::string EmployeeUI::user_menu() {
    return "Choose an option:\n1 - List clients\n2 - Edit client by ID\n3 - Add client\n4 - Remove client\n5 - Back\n━━━━━━━━━━ ✦ ✧ ✦ ━━━━━━━━━━\n";
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

