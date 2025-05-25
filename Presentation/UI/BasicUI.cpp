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
    user_crt = UserController (name, forename);
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
            "2 - Log in\n------------------- * * * -------------------\n";
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


void BasicUI::run_program() {
    cout << display_start_message();
    // insert_name_and_forename();
    cout << dispaly_main_menu();
    int option;
    cout << "Option: ";
    cin >> option;
    cout << endl;
    if (option == 1) {
        return;
    }
    if (option == 2) {
        pair<string,string> email_and_password= insert_email_and_password();
        user_crt.login(email_and_password.first, email_and_password.second);
        auto raw_ptr = user_crt.get_current_user();

        if (!raw_ptr) {
            throw runtime_error("No user is currently logged in.");
        }

        if (dynamic_cast<Employee*>(raw_ptr)) {
            cout<< raw_ptr->get_name()<< endl;
        } else if (dynamic_cast<Customer*>(raw_ptr)) {
           cout<< raw_ptr->get_name()<< endl;
        }
        // else {
        //     throw runtime_error("Logged-in user is of unknown type.");
        // }
    }
}
