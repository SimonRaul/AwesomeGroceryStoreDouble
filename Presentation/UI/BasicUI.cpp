//
// Created by Simon Raul on 5/2/2025.
//

#include "BasicUI.h"
#include <iostream>

using namespace basicUI;

BasicUI::BasicUI() {
    pair<string, string> names = insert_name_and_forename();
    name = names.first;
    forename = names.second;
    user_crt = UserController (name, forename,"Accounts", "clients.txt", "employees.txt");
}

//Displays the message that appears at the start of the program
string BasicUI::display_start_message() {
    string start_message = "+============================================================+\n"
                       "|   Welcome " + name + " " + forename + " to the AWESOME GROCERY STORE 2!       |\n"
                       "+============================================================+\n";

    return start_message;
}


//Method to set the name and forename of the new user
pair<string,string> BasicUI::insert_name_and_forename() {
    string name, forename;
    cout << "Plesase insert your name and forename" << endl;
    cout << "name: " << endl;
    cin >> name;
    cout << endl;
    cout << "forename: " << endl;
    cin >> forename;
    cout << endl;

    return {name, forename};
    // user_crt.set_name(name);
    // new_user.set_forename(forename);
}

//Displays the main menu
string BasicUI::dispaly_main_menu() {
    return "1 - Create an account\n"
            "2 - Log in\n"
            "0 - Exit\n------------------- * * * -------------------\n";
}

pair<string,string> BasicUI::insert_email_and_password() {
    string email, password;
    cout << "Email: " << endl;
    cin >> email;
    cout << endl;
    cout << "Password: " << endl;
    cin >> password;
    cout << endl;
    return {email,password};
}


int BasicUI::input_integer() {
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

float BasicUI::input_float() {
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

std::string BasicUI::input_string() {
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


void BasicUI::run_program() {
    cout << display_start_message();
    while (true) {
        // insert_name_and_forename();
        cout << dispaly_main_menu();
        int option;
        cout << "Option: ";
        option = input_integer();
        cout << endl;
        if (option == 0) {
            break;
        }
        if (option == 1) {
            pair<string,string> name_forename = insert_name_and_forename();
            pair<string, string> email_password = insert_email_and_password();
            string address;
            cout << "Address: " << endl;
            cin>> address;
            user_crt.create_account(name_forename.first, name_forename.second,
                email_password.first, email_password.second, address);
        }
        if (option == 2) {
            pair<string,string> email_and_password= insert_email_and_password();
            user_crt.login(email_and_password.first, email_and_password.second);
            auto raw_ptr = user_crt.get_current_user();

            if (!raw_ptr) {
                throw runtime_error("No user is currently logged in.");
            }

            if (dynamic_cast<Employee*>(raw_ptr)) {
                emp_ui.run_main_menu(dynamic_cast<Employee*>(raw_ptr));

            } else if (dynamic_cast<Customer*>(raw_ptr)) {
                cus_ui.run(dynamic_cast<Customer*>(raw_ptr));
            }
        }
    }
}
